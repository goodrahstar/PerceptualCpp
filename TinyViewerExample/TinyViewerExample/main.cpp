// 
// Sample image viewer code for PCSDK 
//


#include <iostream>
#include "util_pipeline.h"
#include "util_render.h"

using namespace std;


int main(int argc, wchar_t* argv[]) {
	
	UtilPipeline pipeline;
	pipeline.EnableImage(PXCImage::COLOR_FORMAT_DEPTH);
	pipeline.Init();

	UtilRender *render = new UtilRender(L"Image test");
	render->SetSize(320, 240);
	
	while(1)
	{
		if(pipeline.AcquireFrame(false))
		{
			PXCImage *depth = pipeline.QueryImage(PXCImage::IMAGE_TYPE_DEPTH);
			render->RenderFrame(depth);

			// use this to get raw buffer
			//PXCImage::ImageData rgbData;
			//rgb->AcquireAccess(PXCImage::ACCESS_READ, &rgbData);
			//rgbData.planes[0];
			//rgb->ReleaseAccess(&rgbData);
		
			// we must release the frame
			pipeline.ReleaseFrame();
		}
	}

	delete render;
}
