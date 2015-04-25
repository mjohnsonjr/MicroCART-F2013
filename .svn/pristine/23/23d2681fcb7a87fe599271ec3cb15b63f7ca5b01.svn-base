/*
 * QuadCommand.h
 *
 *  Created on: Jan 23, 2014
 *      Author: Michael Johnson
 */

#ifndef QUADCOMMMAND_H_
#define QUADCOMMMAND_H_

/* Array locations, size */
#define PACKET_SIZE 15

#define CUR_POS_ALT 0
#define CUR_POS_LAT 1
#define CUR_POS_LON 2
#define CUR_OR_PITCH 3
#define CUR_OR_ROLL 4
#define CUR_OR_YAW 5

#define TARGET_DIR 6
#define TARGET_POS_ALT 7
#define TARGET_POS_LAT 8
#define TARGET_POS_LON 9
#define TARGET_PITCH 10
#define TARGET_ROLL 11
#define MANUAL_THROTTLE 12
#define AUTO_THROTTLE 13
#define MANUAL_CONTROL 14

#include <vector>


class QuadCommand{

	private:
		mutable volatile float packet[PACKET_SIZE];

	public:

		QuadCommand();
		QuadCommand(float*);
		virtual ~QuadCommand();

		volatile float* getPacket() {
			return packet;
		}

		const int getPacketSize() const {
			return PACKET_SIZE * sizeof(float);
		}
		void setPacket(const float *);
		void setCurrentAltitude(const float);
		void setCurrentLatitude(const float);
		void setCurrentLongitude(const float);
		void setCurrentPitch(const float);
		void setCurrentRoll(const float);
		void setCurrentYaw(const float);

		void setTargetAltitude(const float);
		void setTargetLatitude(const float);
		void setTargetLongitude(const float);
		void setTargetDirection(const float);
		void setTargetPitch(const float);
		void setTargetRoll(const float);
		void setManualThrottle(const float);
		void setAutoThrottle(const bool);
        void setManualControl(const bool);
};


#endif /* QUADCOMMMAND_H_ */
