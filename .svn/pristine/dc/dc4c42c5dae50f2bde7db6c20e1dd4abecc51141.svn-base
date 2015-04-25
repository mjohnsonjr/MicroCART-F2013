
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "vrpn_Connection.h"
#include "vrpn_Tracker.h"

using namespace std;


void VRPN_CALLBACK handle_pos(void*, const vrpn_TRACKERCB t);

int main()
{
	vrpn_Connection *connection;
	
	char connectionName[50];

	strcpy(connectionName, "192.168.0.120:3883");


	connection = vrpn_get_connection_by_name(connectionName);

	vrpn_Tracker_Remote *tracker = new vrpn_Tracker_Remote("UAV", connection);

	tracker->register_change_handler(0, handle_pos);
	usleep(2000);
	
	while(1){
		connection->mainloop();
		tracker->mainloop();
		usleep(3000);
	}

}

void VRPN_CALLBACK handle_pos(void*, const vrpn_TRACKERCB t){

	printf("Tracker Position: (%.4f, %.4f, %.4f) Orientation: (%.2f, %.2f, %.2f, %.2f)\n", t.pos[0], t.pos[1], t.pos[2], t.quat[0], t.quat[1], t.quat[2], t.quat[3]);  

}
