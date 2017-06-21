#pragma once
#include "GPGPU\GPURasterBuffer.h"
#include "GPGPU\OpenCL\OpenCLDevice.h"

#include "Metrics.h"

/* Buffer for open cl raster. */
/* Buffer for open cl raster. */
class OpenCLRasterBuffer :public GPURasterBuffer {

public:

	/*
	 *    Constructor.
	 *
	 *    @param [in,out]	parameter1	If non-null, the first parameter.
	 *    @param 		 	parameter2	The second parameter.
	 */

	OpenCLRasterBuffer(OpenCLDevice*, uint);
	/* Destructor. */
	/* Destructor. */
	~OpenCLRasterBuffer();

	/* Map resources. */
	/* Map resources. */
	void MapResources();
	/* Unmap resources. */
	/* Unmap resources. */
	void UnmapResources();

	/*
	 *    Bind data.
	 *
	 *    @param	parameter1	The first parameter.
	 */

	void BindData(uint);

protected:

private:

};