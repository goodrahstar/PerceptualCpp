// 
// Sample gesture recognition code for PCSDK 
//


#include <iostream>
#include "util_pipeline.h"


using namespace std;


int main(int argc, wchar_t* argv[]) {
	
	UtilPipeline pipeline;
	PXCGesture * gesture;
	
	pipeline.EnableGesture();
	pipeline.Init();


	while(1)
	{
		if(pipeline.AcquireFrame(false))
		{
			gesture = pipeline.QueryGesture();

			// look for the wave gesture for the primary hand
			PXCGesture::Gesture handGesture;
			int i=0;
			while(gesture->QueryGestureData(0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, i++, &handGesture) != PXC_STATUS_ITEM_UNAVAILABLE)
				if(handGesture.label == PXCGesture::Gesture::LABEL_HAND_WAVE)
					cout << "\nwave";
			
			// get the node data for the whole primary hadn (the one that shows up in the view first)
			PXCGesture::GeoNode handNode;
			if(gesture->QueryNodeData(0, PXCGesture::GeoNode::LABEL_BODY_HAND_PRIMARY, &handNode) != PXC_STATUS_ITEM_UNAVAILABLE)
				cout << "Primary hand at x = " << handNode.positionWorld.x << " y = " << handNode.positionWorld.y << " z = " << handNode.positionWorld.z;

			// we must release the frame
			pipeline.ReleaseFrame();
		}
	}
}
