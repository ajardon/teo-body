// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __MOVE_GRIPPER_PORT__
#define __MOVE_GRIPPER_PORT__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#include <yarp/dev/ControlBoardInterfaces.h>

/**
 * @ingroup recordManipulation
 *
 * The MoveGripperPort class.
 *
 */
class MoveGripperPort : public yarp::os::BufferedPort<yarp::os::Bottle> {

    public:

        void setIPositionControl(yarp::dev::IPositionControl *value);
        yarp::dev::IPositionControl *iPositionControlLeft;
        yarp::dev::IPositionControl *iPositionControlRight;

    protected:

        virtual void onRead(yarp::os::Bottle& in);

};


#endif  // __MOVE_GRIPPER_PORT__

