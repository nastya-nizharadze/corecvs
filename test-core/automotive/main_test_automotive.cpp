/**
 * \file main_test_automotive.cpp
 * \brief This is the main file for the test automotive 
 *
 * \date Feb 14, 2011
 * \author alexander
 *
 * \ingroup autotest  
 */

#include <iostream>
#include <vector>
#include "gtest/gtest.h"

#include "core/utils/global.h"

#include "core/math/vector/vector3d.h"
#include "core/math/matrix/matrix44.h"
#include "core/cammodel/cameraParameters.h"
#include "core/math/eulerAngles.h"
#include "core/automotive/FCostFunction.h"
#include "core/automotive/simulation/testSceneSimulator.h"
#include "core/math/mathUtils.h"

using namespace corecvs;

void drawSituation(
        ShiftRotateTransformation realCameraExtr,
        ShiftRotateTransformation realCarMovement,
        ShiftRotateTransformation guessCameraExtr,
        ShiftRotateTransformation guessCarMovement,
        const char *fileName)
{
   FILE *Out = fopen(fileName, "wt");

   const double imageH = 480.0;
   const double imageW = 640.0;

   const Vector2dd imageSize(imageW, imageH);

   PinholeCameraIntrinsics camIntr(imageSize, degToRad(60.0));

   std::vector<FloatFlowVector> *flowVectors = TestSceneSimulator::simulateFlow(camIntr, realCameraExtr, realCarMovement);

   for (unsigned i = 0; i < flowVectors->size(); i++)
   {
       FloatFlowVector flow = flowVectors->at(i);

       double costF = FCostFunction::function(
           flow,
           FCostFunction::FRONT_VIEW_CAMERA,
           camIntr, guessCameraExtr, guessCarMovement);

       double delta = 1e-7;

       FloatFlowVector flowdDU = flow;
       flowdDU.end.x() += delta;
       double costFdv = FCostFunction::function(
           flowdDU, FCostFunction::FRONT_VIEW_CAMERA,
           camIntr, guessCameraExtr, guessCarMovement);

       double FdDU = (costFdv - costF) / delta;


       FloatFlowVector flowdDV = flow;
       flowdDV.end.y() += delta;
       double costFdu = FCostFunction::function(
           flowdDV, FCostFunction::FRONT_VIEW_CAMERA,
           camIntr, guessCameraExtr, guessCarMovement);

       double FdDV = (costFdu - costF) / delta;


       fprintf(Out, "%lf %lf %lf %lf %lf %lf %lf\n",
               flow.start.x(),
               flow.start.y(),
               flow.end.x(),
               flow.end.y(),
               costF,
               FdDU,
               FdDV );
   }

   delete_safe(flowVectors);


    fclose(Out);
}


//int main (int /*argC*/, char ** /*argV*/)
TEST(Automotive, main)
{
    Vector3dd cameraPos(-200.0,0.0,0.0);
    ShiftRotateTransformation  realCameraExtr(EulerAngles(0.0,0.0,0.0), cameraPos);

    Vector3dd carShift(30.0,0.0,0.0);

    ShiftRotateTransformation forwardCarMovement (EulerAngles(0.0, 0.0,  0.0 ), carShift);
    ShiftRotateTransformation turnLeftCarMovement(EulerAngles(0.0, 0.0, -0.05), carShift);
    ShiftRotateTransformation pitchUpCarMovement (EulerAngles(0.0, 0.05, 0.0 ), carShift);

    ShiftRotateTransformation cameraExtrWrongPitch(EulerAngles(degToRad(30.0), 0.0,  0.0), cameraPos);
    ShiftRotateTransformation cameraExtrWrongYaw  (EulerAngles(0.05, degToRad(30.0), 0.0), cameraPos);


    drawSituation(realCameraExtr, forwardCarMovement,  realCameraExtr, forwardCarMovement,  "DriveForward-Ok.txt");
    drawSituation(realCameraExtr, turnLeftCarMovement, realCameraExtr, turnLeftCarMovement, "RotateLeft-Ok.txt");
    drawSituation(realCameraExtr, pitchUpCarMovement,  realCameraExtr, pitchUpCarMovement,  "PitchUp-Ok.txt");

    drawSituation(realCameraExtr, forwardCarMovement, cameraExtrWrongPitch, forwardCarMovement, "CamPitch-Wrong.txt");
    drawSituation(realCameraExtr, forwardCarMovement, cameraExtrWrongYaw  , forwardCarMovement, "CamYaw-Wrong.txt");

    drawSituation(realCameraExtr, forwardCarMovement, realCameraExtr, pitchUpCarMovement, "CarPitch-Wrong.txt");
    drawSituation(realCameraExtr, forwardCarMovement, realCameraExtr, turnLeftCarMovement, "CarYaw-Wrong.txt");

//    return 0;
}
