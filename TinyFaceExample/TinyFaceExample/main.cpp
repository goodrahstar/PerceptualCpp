// 
// Sample face detection code for PCSDK 
//


#include <iostream>
#include "util_pipeline.h"


using namespace std;


int main(int argc, wchar_t* argv[]) {

	map<PXCFaceAnalysis::Landmark::Label, string> faceLandmarkNames;
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_INNER_CORNER] = "left eye inner";
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_LEFT_EYE_OUTER_CORNER] = "left eye outer";
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_INNER_CORNER] = "right eye inner";
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_RIGHT_EYE_OUTER_CORNER] = "right eye outer";
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_MOUTH_LEFT_CORNER] = "mouth left";
	faceLandmarkNames[PXCFaceAnalysis::Landmark::LABEL_MOUTH_RIGHT_CORNER] = "mouth right";


	UtilPipeline pipeline;
	PXCFaceAnalysis *faceAnalysis;

	pipeline.EnableFaceLocation();
	pipeline.EnableFaceLandmark();
	pipeline.Init();


	while(1)
	{
		if(pipeline.AcquireFrame(false))
		{
			faceAnalysis = pipeline.QueryFace();

			// get the face id for the first face
			pxcUID faceId;
			if(faceAnalysis->QueryFace(0, &faceId) != PXC_STATUS_ITEM_UNAVAILABLE)
			{
				// get the face location
				PXCFaceAnalysis::Detection *detector = faceAnalysis->DynamicCast<PXCFaceAnalysis::Detection>();
				PXCFaceAnalysis::Detection::Data faceData;
				if(detector->QueryData(faceId, &faceData) != PXC_STATUS_ITEM_UNAVAILABLE)
					cout << "\nFace " << faceId << " at location " << faceData.rectangle.x << " " << faceData.rectangle.y;

				PXCFaceAnalysis::Landmark *landmarkDetector = faceAnalysis->DynamicCast<PXCFaceAnalysis::Landmark>();
				PXCFaceAnalysis::Landmark::LandmarkData landmarkData;
				int i=0;
				while(landmarkDetector->QueryLandmarkData(faceId, PXCFaceAnalysis::Landmark::LABEL_6POINTS, i++, &landmarkData) != PXC_STATUS_ITEM_UNAVAILABLE)
					cout << "\nFace landmark " << faceLandmarkNames[landmarkData.label] << " at x = " << landmarkData.position.x << " y = " << landmarkData.position.y;
			}

			pipeline.ReleaseFrame();
		}
	}
}
