// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "MotorIpos.hpp"

// ------------------- ITorqueControlRaw Related ------------------------------------

bool teo::MotorIpos::getRefTorqueRaw(int j, double *t) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::setRefTorqueRaw(int j, double t) {
    CD_INFO("(%d,%f)\n",j,t);

    //-- Check index within range
    if ( j!= 0 ) return false;

    //*************************************************************
    uint8_t msg_ref_torque[]={0x23,0x1C,0x20,0x00,0x00,0x00,0x00,0x00}; // put 23 because it is a target

    int sendRefTorque = t * (65520.0/20.0);
    //memcpy(msg_ref_torque+4,&sendRefTorque,4);  // was +6 not +4, but +6 seems terrible with ,4!
    memcpy(msg_ref_torque+6,&sendRefTorque,2);

    if(! send(0x600, 8, msg_ref_torque) )
    {
        CD_ERROR("Could not send refTorque. %s\n", msgToStr(0x600, 8, msg_ref_torque).c_str() );
        return false;
    }
    CD_SUCCESS("Sent refTorque. %s\n", msgToStr(0x600, 8, msg_ref_torque).c_str() );
    //*************************************************************

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getBemfParamRaw(int j, double *bemf) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::setBemfParamRaw(int j, double bemf) {
    CD_INFO("(%d,%f)\n",j,bemf);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::setTorquePidRaw(int j, const Pid &pid) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorqueRaw(int j, double *t) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    //*************************************************************
    uint8_t msg_getCurrent[]={0x40,0x7E,0x20,0x00}; // Query current. Ok only 4.

    if(! send(0x600, 4, msg_getCurrent) )
    {
        CD_ERROR("Could not send msg_getCurrent. %s\n", msgToStr(0x600, 4, msg_getCurrent).c_str() );
        return false;
    }
    CD_SUCCESS("Sent msg_getCurrent. %s\n", msgToStr(0x600, 4, msg_getCurrent).c_str() );
    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Time::delay(DELAY);  // Must delay as it will be from same driver.
    //* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    getTorqueReady.wait();
    *t = getTorque;
    getTorqueReady.post();

    //*************************************************************
    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorqueRangeRaw(int j, double *min, double *max) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::setTorqueErrorLimitRaw(int j, double limit) {
    CD_INFO("(%d,%f)\n",j,limit);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorqueErrorRaw(int j, double *err) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorquePidOutputRaw(int j, double *out) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorquePidRaw(int j, Pid *pid) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::getTorqueErrorLimitRaw(int j, double *limit) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::resetTorquePidRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::disableTorquePidRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::enableTorquePidRaw(int j) {
    CD_INFO("(%d)\n",j);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------

bool teo::MotorIpos::setTorqueOffsetRaw(int j, double v) {
    CD_INFO("(%d,%f)\n",j,v);

    //-- Check index within range
    if ( j != 0 ) return false;

    CD_WARNING("Not implemented yet (motoripos).\n");

    return true;
}

// -----------------------------------------------------------------------------
