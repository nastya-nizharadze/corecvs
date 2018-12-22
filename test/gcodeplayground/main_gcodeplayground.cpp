#include <fstream>

#include "core/fileformats/gcodeLoader.h"
#include "core/fileformats/pltLoader.h"


using namespace std;
using namespace corecvs;




int vynilCutter (double offset)
{
    CORE_UNUSED(offset);

    std::string input = "in.gcode";
    std::string output = "out.gcode";



    GCodeProgram program;
    GcodeLoader loader;

    ifstream file;
    file.open(input, ios::in);
    if (file.fail())
    {
        SYNC_PRINT(("g code playground::load(): Can't open mesh file <%s>\n", input.c_str()));
        return false;
    }

    loader.loadGcode(file, program);

    GCodeProgram programR;





    ofstream outfile;
    outfile.open(output, std::ostream::out);
    loader.saveGcode(outfile, programR);
    outfile.close();
    return 0;
}



int main1 (int argc, char **argv)
{
    std::string input = "";
    std::string output = "a.gcode";


    if (argc == 2)
    {
        input = argv[1];
    } else if (argc == 3)
    {
        input  = argv[1];
        output = argv[2];
    } else {
        SYNC_PRINT(("Usage rawconverter <input.gcode> [<output.gcode>]\n"));
        SYNC_PRINT((" default output is a.gcode \n"));
        return 1;
    }

    GCodeProgram program;
    GcodeLoader loader;

    ifstream file;
    file.open(input, ios::in);
    if (file.fail())
    {
        SYNC_PRINT(("g code playground::load(): Can't open mesh file <%s>\n", input.c_str()));
        return false;
    }

    loader.loadGcode(file, program);

    double z = 0;
    double percentAdd   = (250.0-40.0) / 6.0;
    double percentStart = 40.0;

    for (size_t i = 0; i < program.program.size(); i++)
    {
        GCodeProgram::Code &c = program.program[i];
        if (c.hasParameter('z')) {
            z = c.getParameter('z');
        }

        int part = 0;
        if (z > 2) part = (z - 2) / 10;

        double factor = percentStart + part * percentAdd;

        if (c.hasParameter('f')) {
            c.setParameter('f', c.getParameter('f') * (factor / 100.0));
        }

    }

    ofstream outfile;
    outfile.open(output, std::ostream::out);
    loader.saveGcode(outfile, program);
    outfile.close();
    return 0;
}


int main (int argc, char **argv)
{
    HPGLLoader loader;
    HPGLProgram program;

    ifstream file;
    std::string input = argv[1];

    file.open(input, ios::in);
    if (file.fail())
    {
        SYNC_PRINT(("plt playground::load(): Can't open plt file <%s>\n", input.c_str()));
        return false;
    }

    loader.loadHPGLcode(file, program);

    /*Prepare output*/
    ofstream ofile;
    ofile.open(input + ".gcode", ios::out);

    ofile <<
             "G21         ; Set units to mm\n"
             "G90         ; Absolute positioning\n"
             "M221 S100   ; Power on\n"
             "G1 F500     ; Feed rate\n"
             "\n";



    /* Mesh output */


    Mesh3D mesh;
    mesh.switchColor();

    Vector3dd pos(0.0);
    mesh.setColor(RGBColor::Green());
    bool on = false;

    bool moved = true;

    for (size_t t = 0; t < program.program.size(); t++)
    {
        HPGLProgram::Record &r = program.program[t];

        if (r.command == "PA") {
            Vector2dd p1(r.params[0], r.params[1]);

            Vector2dd gout = (p1 / 40.0) - Vector2dd(0, 100);

            Vector3dd meshout(gout, 0.0);

            mesh.addLine(pos, meshout);
            pos = meshout;


            if (on) {
                ofile << "G1 X" << gout.x() << " Y" << gout.y() << " S1.0" << endl;
            } else {
                ofile << "G0 X" << gout.x() << " Y" << gout.y() << endl;
            }

            moved = true;
        }
        if (r.command == "PU") {
            if (!moved)
            {
                 ofile << "G1 X" << pos.x() - 0.1 << " Y" << pos.y()       << " S1.0" << endl;
                 ofile << "G1 X" << pos.x() + 0.1 << " Y" << pos.y()       << " S1.0" << endl;
                 ofile << "G1 X" << pos.x()       << " Y" << pos.y()       << " S1.0" << endl;
                 ofile << "G1 X" << pos.x() - 0.1 << " Y" << pos.y() - 0.1 << " S1.0" << endl;
                 ofile << "G1 X" << pos.x() + 0.1 << " Y" << pos.y() + 0.1 << " S1.0" << endl;
                 ofile << "G1 X" << pos.x()       << " Y" << pos.y()       << " S1.0" << endl;
            }
            on = false;
            mesh.setColor(RGBColor::Red());
        }

        if (r.command == "PD") {
            on = true;
            mesh.setColor(RGBColor::Green());
            moved = false;
        }

    }

    mesh.dumpPLY(input + ".ply");

    ofile << "M5          ; Switch tool offEnd" << endl;
    ofile << "M400" << endl;
    ofile << "G0 X0 Y0" << endl;
    ofile << "M221   S0" << endl;
    ofile.close();
    return 0;
}
