#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdlib.h>
#include <atlimage.h>
#include "globals.h"

/* implements the framebuffer. you might want to modify it to add depth buffering and other capabilities */
class FrameBuffer {
	private:
		int width, height;

		/* all the buffers are defined from the lower left corner of the screen */
		u08 *color_buffer;		/* color buffer is unsigned bytes buffer size 3*w*h */
		float *depth_buffer;

	public:
		/* constructor */
		FrameBuffer(int _w, int _h) {
			width = _w;		height = _h;

			/* allocate the buffer */
			color_buffer = (u08 *)malloc(sizeof(u08) * width * height * 3);		
			depth_buffer = (float *)malloc(sizeof(float) * width * height);
		};

		/* destructor */
		~FrameBuffer() {
			if (color_buffer)
				free(color_buffer);
			if (depth_buffer)
				free(depth_buffer);
		};

		void setColorBuffer(int x, int y, float r, float g, float b) {
			*getColorPtr(x, y) = r;
			*(getColorPtr(x, y) + 1) = g;
			*(getColorPtr(x, y) + 2) = b;
		}

		/* get color ptr */
		u08 *getColorPtr(int x, int y) {
			return (color_buffer + ((y * width + x)*3));
		};

		void setDepthBuffer(int x, int y, float z) {
			*getDepthPtr(x, y) = z;
		}

		float *getDepthPtr(int x, int y) {
			return (depth_buffer + (y * width + x));
		};

		float FrameBuffer::getDepth(int x, int y) {
			return depth_buffer[(y*width) + x];
		}

		void FrameBuffer::clear(void) {
			memset(color_buffer, 0, (sizeof(u08) * width * height * 3));

			// Initialize depth-buffer with very large number
			float *ptr = getDepthPtr(0, 0);
			for (int i = 0; i < width; i++)
				for (int j = 0; j < height; j++)
				{
					*ptr = 9999999999.0;
					ptr++;
				}
		}

		void copyColorBuffer(CImage *image);
		void dumpColorBufferToFile(char *name);
		void dumpToScreen(void);
};

#endif		/* FRAMEBUFFER_H */
