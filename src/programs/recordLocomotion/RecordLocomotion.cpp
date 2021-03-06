// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RecordLocomotion.hpp"

/************************************************************************/
RecordLocomotion::RecordLocomotion() { }

/************************************************************************/
bool RecordLocomotion::configure(yarp::os::ResourceFinder &rf) {

    int ptModeMs = rf.check("ptModeMs",yarp::os::Value(DEFAULT_PT_MODE_MS),"PT mode miliseconds").asInt();
    CD_INFO("Using ptModeMs: %d (default: %d).\n",ptModeMs,int(DEFAULT_PT_MODE_MS));

    //-- Open file for writing.
    std::string fileName = rf.check("file",yarp::os::Value(DEFAULT_FILE_NAME),"file name").asString();
    CD_INFO("Using file: %s (default: " DEFAULT_FILE_NAME ").\n",fileName.c_str());
    filePtr = ::fopen (fileName.c_str(),"w");
    if( ! filePtr ) {
        CD_PERROR("Could not open file: %s.\n",fileName.c_str());
        return false;
    }
    CD_SUCCESS("Opened file: %s.\n",fileName.c_str());

    //-- left leg --
    std::string leftLegIni = rf.findFileByName("../locomotion/leftLeg.ini");

    yarp::os::Property leftLegOptions;
    if (! leftLegOptions.fromConfigFile(leftLegIni) ) {  //-- Put first because defaults to wiping out.
        CD_ERROR("Could not configure from \"leftLeg.ini\".\n");
        return false;
    }
    CD_SUCCESS("Configured left leg from %s.\n",leftLegIni.c_str());
    leftLegOptions.put("device","bodybot");
    if (rf.check("home")) leftLegOptions.put("home",1);
    if (rf.check("reset")) leftLegOptions.put("reset",1);

    leftLegDevice.open(leftLegOptions);
    
    if (!leftLegDevice.isValid()) {
        CD_ERROR("leftLegDevice instantiation not worked.\n");
        CD_ERROR("Be sure CMake \"ENABLE_BodyYarp_bodybot\" variable is set \"ON\"\n");
        CD_ERROR("\"SKIP_bodybot is set\" --> should be --> \"ENABLE_bodybot is set\"\n");
        // robotDevice.close();  // un-needed?
        return false;
    }

    //-- right leg --
    std::string rightLegIni = rf.findFileByName("../locomotion/rightLeg.ini");

    yarp::os::Property rightLegOptions;
    if (! rightLegOptions.fromConfigFile(rightLegIni) ) {  //-- Put first because defaults to wiping out.
        CD_ERROR("Could not configure from \"rightLeg.ini\".\n");
        return false;
    }
    CD_SUCCESS("Configured right leg from %s.\n",rightLegIni.c_str());
    rightLegOptions.put("name","/teo/rightLeg");
    rightLegOptions.put("device","bodybot");
    if (rf.check("home")) rightLegOptions.put("home",1);
    if (rf.check("reset")) rightLegOptions.put("reset",1);

    rightLegDevice.open(rightLegOptions);

    if (!rightLegDevice.isValid()) {
        CD_ERROR("rightLegDevice instantiation not worked.\n");
        CD_ERROR("Be sure CMake \"ENABLE_BodyYarp_bodybot\" variable is set \"ON\"\n");
        CD_ERROR("\"SKIP_bodybot is set\" --> should be --> \"ENABLE_bodybot is set\"\n");
        // robotDevice.close();  // un-needed?
        return false;
    }

    //-- Configure the thread.
    recordRateThread.setFilePtr(filePtr);

    //-- Obtain manipulator interfaces.
    if ( ! leftLegDevice.view( recordRateThread.leftLegEnc ) ) {
        CD_ERROR("Could not obtain leftLegEnc.\n");
        return false;
    }
    CD_SUCCESS("Obtained leftLegEnc.\n");

    if ( ! leftLegDevice.view( recordRateThread.leftLegTrq ) ) {
        CD_ERROR("Could not obtain leftLegTrq.\n");
        return false;
    }
    CD_SUCCESS("Obtained leftLegTrq.\n");

    if ( ! rightLegDevice.view( recordRateThread.rightLegEnc ) ) {
        CD_ERROR("Could not obtain rightLegEnc.\n");
        return false;
    }
    CD_SUCCESS("Obtained rightLegEnc.\n");

    if ( ! rightLegDevice.view( recordRateThread.rightLegTrq ) ) {
        CD_ERROR("Could not obtain rightLegTrq.\n");
        return false;
    }
    CD_SUCCESS("Obtained rightLegTrq.\n");

    //-- Do stuff.
    CD_INFO("setTorqueMode in 1 second...\n");
    yarp::os::Time::delay(1);

    recordRateThread.leftLegEnc->getAxes( &(recordRateThread.leftLegNumMotors) );
    for(int i=0; i<recordRateThread.leftLegNumMotors; i++)
        recordRateThread.leftLegTrq->setRefTorque(i,0);

    recordRateThread.rightLegEnc->getAxes( &(recordRateThread.rightLegNumMotors) );
    for(int i=0; i< recordRateThread.rightLegNumMotors; i++)
        recordRateThread.rightLegTrq->setRefTorque(i,0);

    recordRateThread.leftLegTrq->setTorqueMode();
    recordRateThread.rightLegTrq->setTorqueMode();

    //-- Start the thread.
    CD_INFO("Start thread in 1 second...\n");
    yarp::os::Time::delay(1);
    recordRateThread.setRate(ptModeMs);
    recordRateThread.start();

    return true;
}

/************************************************************************/

bool RecordLocomotion::updateModule() {
    //printf("RecordLocomotion alive...\n");
    return true;
}

/************************************************************************/

bool RecordLocomotion::close() {

    recordRateThread.stop();

    leftLegDevice.close();
    rightLegDevice.close();

    ::fclose(filePtr);

    return true;
}

/************************************************************************/
