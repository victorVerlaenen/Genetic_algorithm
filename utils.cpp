#include "pch.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
#include <algorithm>
#include <iostream>
#include "utils.h"

namespace utils
{
#pragma region OpenGLDrawFunctionality
	void ClearBackground(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void ClearBackground()
	{
		ClearBackground(185.0f / 255.0f, 211.0f / 255.0f, 238.0f / 255.0f);
	}
	void SetColor(float r, float g, float b, float a)
	{
		glColor4f(r, g, b, a);
	}

	void SetColor(const Color4f& color)
	{
		glColor4f(color.r, color.g, color.b, color.a);
	}

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
	}

	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth)
	{
		DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
	}

	void DrawRect(float left, float bottom, float width, float height, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3)
	{
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth)
	{
		DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
	}

	void DrawRect(const Rectf& rect, float lineWidth)
	{
		DrawRect(rect.left, rect.bottom, rect.width, rect.height, lineWidth);
	}

	void FillRect(float left, float bottom, float width, float height)
	{
		glBegin(GL_POLYGON);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void FillRect(const Point2f& bottomLeft, float width, float height)
	{
		FillRect(bottomLeft.x, bottomLeft.y, width, height);
	}

	void FillRect(const Rectf& rect)
	{
		FillRect(rect.left, rect.bottom, rect.width, rect.height);
	}

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth)
	{
		DrawEllipse(center.x, center.y, radX, radY, lineWidth);
	}

	void DrawEllipse(const Ellipsef& ellipse, float lineWidth)
	{
		DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth);
	}

	void FillEllipse(float centerX, float centerY, float radX, float radY)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void FillEllipse(const Ellipsef& ellipse)
	{
		FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
	}

	void FillEllipse(const Point2f& center, float radX, float radY)
	{
		FillEllipse(center.x, center.y, radX, radY);
	}

	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}

		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		{
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();

	}

	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
	}

	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			glVertex2f(centerX, centerY);
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();
	}

	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle)
	{
		FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
	}

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed, float lineWidth)
	{
		DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
	}

	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth)
	{
		glLineWidth(lineWidth);
		closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}

	void FillPolygon(const std::vector<Point2f>& vertices)
	{
		FillPolygon(vertices.data(), vertices.size());
	}

	void FillPolygon(const Point2f* pVertices, size_t nrVertices)
	{
		glBegin(GL_POLYGON);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}
#pragma endregion OpenGLDrawFunctionality


#pragma region textureImplementations

	bool TextureFromFile(const std::string& path, Texture& texture)
	{
		//Load file for use as an image in a new surface.
		SDL_Surface* pLoadedSurface = IMG_Load(path.c_str());
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromFile: SDL Error when calling IMG_Load: " << SDL_GetError() << std::endl;
			return false;
		}

		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture)
	{
		// Create font
		TTF_Font* pFont{};
		pFont = TTF_OpenFont(fontPath.c_str(), ptSize);
		if (pFont == nullptr)
		{
			std::cout << "TextureFromString: Failed to load font! SDL_ttf Error: " << TTF_GetError();
			std::cin.get();
			return false;
		}

		// Create texture using this fontand close font afterwards
		bool textureOk = TextureFromString(text, pFont, textColor, texture);
		TTF_CloseFont(pFont);

		return textureOk;
	}

	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& color, Texture& texture)
	{
		//Render text surface
		SDL_Color textColor{};
		textColor.r = Uint8(color.r * 255);
		textColor.g = Uint8(color.g * 255);
		textColor.b = Uint8(color.b * 255);
		textColor.a = Uint8(color.a * 255);

		SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
		//SDL_Surface* pLoadedSurface = TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromString: Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
			return false;
		}

		// copy to video memory
		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	void TextureFromSurface(const SDL_Surface* pSurface, Texture& texture)
	{
		//Get image dimensions
		texture.width = float(pSurface->w);
		texture.height = float(pSurface->h);

		// Get pixel format information and translate to OpenGl format
		GLenum pixelFormat{ GL_RGB };
		switch (pSurface->format->BytesPerPixel)
		{
		case 3:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGB;
			}
			else
			{
				pixelFormat = GL_BGR;
			}
			break;
		case 4:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGBA;
			}
			else
			{
				pixelFormat = GL_BGRA;
			}
			break;
		default:
			std::cerr << "TextureFromSurface error: Unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";;
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Generate an array of textures.  We only want one texture (one element array), so trick
		//it by treating "texture" as array of length one.
		glGenTextures(1, &texture.id);

		//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
		//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// check for errors.
		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			std::cerr << "TextureFromSurface, error binding textures, Error id = " << e << '\n';
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Specify the texture's data.  This function is a bit tricky, and it's hard to find helpful documentation.  A summary:
		//   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
		//               0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
		//                         not cached smaller copies)
		//         GL_RGBA:    Specifies the number of color components in the texture.
		//                     This is how OpenGL will store the texture internally (kinda)--
		//                     It's essentially the texture's type.
		//      surface->w:    The width of the texture
		//      surface->h:    The height of the texture
		//               0:    The border.  Don't worry about this if you're just starting.
		//     pixelFormat:    The format that the *data* is in--NOT the texture! 
		//GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
		//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
		//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
		//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
		// surface->pixels:    The actual data.  As above, SDL's array of bytes.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

		//Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
		//*smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
		//each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
		//further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
		//them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void DeleteTexture(Texture& texture)
	{
		glDeleteTextures(1, &texture.id);
	}

	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect)
	{
		Rectf dstRect{ dstBottomLeft.x, dstBottomLeft.y, srcRect.width, srcRect.height };
		DrawTexture(texture, dstRect, srcRect);
	}


	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect)
	{
		// Determine texture coordinates using srcRect and default destination width and height
		float textLeft{};
		float textRight{};
		float textTop{};
		float textBottom{};

		float defaultDstWidth{};
		float defaultDstHeight{};
		if (!(srcRect.width > 0.0f && srcRect.height > 0.0f)) // No srcRect specified
		{
			// Use complete texture
			textLeft = 0.0f;
			textRight = 1.0f;
			textTop = 0.0f;
			textBottom = 1.0f;

			defaultDstHeight = texture.height;
			defaultDstWidth = texture.width;
		}
		else // srcRect specified
		{
			// Convert to the range [0.0, 1.0]
			textLeft = srcRect.left / texture.width;
			textRight = (srcRect.left + srcRect.width) / texture.width;
			textTop = (srcRect.bottom - srcRect.height) / texture.height;
			textBottom = srcRect.bottom / texture.height;

			defaultDstHeight = srcRect.height;
			defaultDstWidth = srcRect.width;
		}

		// Determine vertex coordinates
		float vertexLeft{ dstRect.left };
		float vertexBottom{ dstRect.bottom };
		float vertexRight{};
		float vertexTop{};
		if (!(dstRect.width > 0.0f && dstRect.height > 0.0f)) // If no size specified use default size
		{
			vertexRight = vertexLeft + defaultDstWidth;
			vertexTop = vertexBottom + defaultDstHeight;
		}
		else
		{
			vertexRight = vertexLeft + dstRect.width;
			vertexTop = vertexBottom + dstRect.height;
		}

		// Tell opengl which texture we will use
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// set the texture mode https://open.gl/textures
		float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		// Draw
		glEnable(GL_TEXTURE_2D);
		{
			glBegin(GL_QUADS);
			{
				glTexCoord2f(textLeft, textBottom);
				glVertex2f(vertexLeft, vertexBottom);

				glTexCoord2f(textLeft, textTop);
				glVertex2f(vertexLeft, vertexTop);

				glTexCoord2f(textRight, textTop);
				glVertex2f(vertexRight, vertexTop);

				glTexCoord2f(textRight, textBottom);
				glVertex2f(vertexRight, vertexBottom);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
#pragma endregion textureImplementations


#pragma region CollisionFunctionality
	bool utils::IsPointInRect(const Point2f& p, const Rectf& r)
	{
		return (p.x >= r.left &&
			p.x <= r.left + r.width &&
			p.y >= r.bottom &&
			p.y <= r.bottom + r.height);
	}

	bool utils::IsPointInCircle(const Point2f& p, const Circlef& c)
	{
		float squaredDist{ (p.x - c.center.x) * (p.x - c.center.x) + (p.y - c.center.y) * (p.y - c.center.y) };
		float squaredRadius{ c.radius * c.radius };
		return (squaredRadius >= squaredDist);
	}

	bool utils::IsOverlapping(const Point2f& a, const Point2f& b, const Rectf& r)
	{
		// if one of the line segment end points is in the rect
		if (utils::IsPointInRect(a, r) || utils::IsPointInRect(b, r))
		{
			return true;
		}

		HitInfo hitInfo{};
		Point2f vertices[]{ Point2f {r.left, r.bottom},
			Point2f{ r.left + r.width, r.bottom },
			Point2f{ r.left + r.width, r.bottom + r.height },
			Point2f{ r.left, r.bottom + r.height } };

		return Raycast(vertices, 4, a, b, hitInfo);
	}

	bool utils::IsOverlapping(const Rectf& r1, const Rectf& r2)
	{
		// If one rectangle is on left side of the other
		if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
		{
			return false;
		}

		// If one rectangle is under the other
		if (r1.bottom > (r2.bottom + r2.height) || r2.bottom > (r1.bottom + r1.height))
		{
			return false;
		}

		return true;
	}

	bool utils::IsOverlapping(const Rectf& r, const Circlef& c)
	{
		// Is center of circle in the rectangle?
		if (IsPointInRect(c.center, r))
		{
			return true;
		}
		// Check line segments
		if (utils::DistPointLineSegment(c.center, Point2f{ r.left, r.bottom }, Point2f{ r.left, r.bottom + r.height }) <= c.radius)
		{
			return true;
		}
		if (utils::DistPointLineSegment(c.center, Point2f{ r.left, r.bottom }, Point2f{ r.left + r.width, r.bottom }) <= c.radius)
		{
			return true;
		}
		if (utils::DistPointLineSegment(c.center, Point2f{ r.left + r.width, r.bottom + r.height }, Point2f{ r.left, r.bottom + r.height }) <= c.radius)
		{
			return true;
		}
		if (utils::DistPointLineSegment(c.center, Point2f{ r.left + r.width, r.bottom + r.height }, Point2f{ r.left + r.width, r.bottom }) <= c.radius)
		{
			return true;
		}
		return false;
	}

	bool utils::IsOverlapping(const Circlef& c1, const Circlef& c2)
	{
		// squared distance between centers
		float xDistance{ c1.center.x - c2.center.x };
		float yDistance{ c1.center.y - c2.center.y };
		float squaredDistance{ xDistance * xDistance + yDistance * yDistance };

		float squaredTouchingDistance{ (c1.radius + c2.radius) * (c1.radius + c2.radius) };
		return (squaredDistance < squaredTouchingDistance);
	}

	bool utils::IsOverlapping(const Point2f& a, const Point2f& b, const Circlef& c)
	{
		return utils::DistPointLineSegment(c.center, a, b) <= c.radius;
	}

	bool utils::IsOverlapping(const std::vector<Point2f>& vertices, const Circlef& c)
	{
		return IsOverlapping(vertices.data(), vertices.size(), c);
	}

	bool utils::IsOverlapping(const Point2f* vertices, size_t nrVertices, const Circlef& c)
	{
		// Verify whether one of vertices is in circle
		for (size_t i{ 0 }; i < nrVertices; ++i)
		{
			if (IsPointInCircle(vertices[i], c))
			{
				return true;
			}
		}

		// Verify whether one of the polygon edges overlaps with circle
		for (size_t i{ 0 }; i < nrVertices; ++i)
		{
			if (DistPointLineSegment(c.center, vertices[i], vertices[(i + 1) % nrVertices]) <= c.radius)
			{
				return true;
			}
		}

		// No overlapping with edges, verify whether circle is completely inside the polygon
		if (IsPointInPolygon(c.center, vertices, nrVertices))
		{
			return true;
		}
		return false;
	}

	bool utils::IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices)
	{
		return IsPointInPolygon(p, vertices.data(), vertices.size());
	}

	bool utils::IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices)
	{
		if (nrVertices < 2)
		{
			return false;
		}
		// 1. First do a simple test with axis aligned bounding box around the polygon
		float xMin{ vertices[0].x };
		float xMax{ vertices[0].x };
		float yMin{ vertices[0].y };
		float yMax{ vertices[0].y };
		for (size_t idx{ 1 }; idx < nrVertices; ++idx)
		{
			if (xMin > vertices[idx].x)
			{
				xMin = vertices[idx].x;
			}
			if (xMax < vertices[idx].x)
			{
				xMax = vertices[idx].x;
			}
			if (yMin > vertices[idx].y)
			{
				yMin = vertices[idx].y;
			}
			if (yMax < vertices[idx].y)
			{
				yMax = vertices[idx].y;
			}
		}
		if (p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax)
		{
			return false;
		}

		// 2. Draw a virtual ray from anywhere outside the polygon to the point 
		//    and count how often it hits any side of the polygon. 
		//    If the number of hits is even, it's outside of the polygon, if it's odd, it's inside.
		int numberOfIntersectionPoints{ 0 };
		Point2f p2{ xMax + 10.0f, p.y }; // Horizontal line from point to point outside polygon (p2)

		// Count the number of intersection points
		float lambda1{}, lambda2{};
		for (size_t i{ 0 }; i < nrVertices; ++i)
		{
			if (IntersectLineSegments(vertices[i], vertices[(i + 1) % nrVertices], p, p2, lambda1, lambda2))
			{
				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
				{
					++numberOfIntersectionPoints;
				}
			}
		}
		if (numberOfIntersectionPoints % 2 == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool utils::IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon)
	{
		bool intersecting{ false };

		Vector2f p1p2{ p1, p2 };
		Vector2f q1q2{ q1, q2 };

		// Cross product to determine if parallel
		float denom = p1p2.CrossProduct(q1q2);

		// Don't divide by zero
		if (std::abs(denom) > epsilon)
		{
			intersecting = true;

			Vector2f p1q1{ p1, q1 };

			float num1 = p1q1.CrossProduct(q1q2);
			float num2 = p1q1.CrossProduct(p1p2);
			outLambda1 = num1 / denom;
			outLambda2 = num2 / denom;
		}
		else // are parallel
		{
			// Connect start points
			Vector2f p1q1{ p1, q1 };

			// Cross product to determine if segments and the line connecting their start points are parallel, 
			// if so, than they are on a line
			// if not, then there is no intersection
			if (std::abs(p1q1.CrossProduct(q1q2)) > epsilon)
			{
				return false;
			}

			// Check the 4 conditions
			outLambda1 = 0;
			outLambda2 = 0;
			if (utils::IsPointOnLineSegment(p1, q1, q2) ||
				utils::IsPointOnLineSegment(p2, q1, q2) ||
				utils::IsPointOnLineSegment(q1, p1, p2) ||
				utils::IsPointOnLineSegment(q2, p1, p2))
			{
				intersecting = true;
			}
		}
		return intersecting;
	}

	bool utils::Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
	{
		return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
	}

	bool utils::Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
	{
		if (nrVertices == 0)
		{
			return false;
		}

		std::vector<HitInfo> hits;

		Rectf r1, r2;
		// r1: minimal AABB rect enclosing the ray
		r1.left = std::min(rayP1.x, rayP2.x);
		r1.bottom = std::min(rayP1.y, rayP2.y);
		r1.width = std::max(rayP1.x, rayP2.x) - r1.left;
		r1.height = std::max(rayP1.y, rayP2.y) - r1.bottom;

		// Line-line intersections.
		for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
		{
			// Consider line segment between 2 consecutive vertices
			// (modulo to allow closed polygon, last - first vertice)
			Point2f q1 = vertices[(idx + 0) % nrVertices];
			Point2f q2 = vertices[(idx + 1) % nrVertices];

			// r2: minimal AABB rect enclosing the 2 vertices
			r2.left = std::min(q1.x, q2.x);
			r2.bottom = std::min(q1.y, q2.y);
			r2.width = std::max(q1.x, q2.x) - r2.left;
			r2.height = std::max(q1.y, q2.y) - r2.bottom;

			if (IsOverlapping(r1, r2))
			{
				float lambda1{};
				float lambda2{};
				if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
				{
					if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
					{
						HitInfo linesHitInfo{};
						linesHitInfo.lambda = lambda1;
						linesHitInfo.intersectPoint = Point2f{ rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
						linesHitInfo.normal = Vector2f{ q2 - q1 }.Orthogonal().Normalized();
						hits.push_back(linesHitInfo);
					}
				}
			}
		}

		if (hits.size() == 0)
		{
			return false;
		}

		// Get closest intersection point and copy it into the hitInfo parameter
		hitInfo = *std::min_element
		(
			hits.begin(), hits.end(),
			[](const HitInfo& first, const HitInfo& last)
			{
				return first.lambda < last.lambda;
			}
		);
		return true;
	}

	bool  utils::IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
	{
		Vector2f ap{ a, p }, bp{ b, p };
		// If not on same line, return false
		if (abs(ap.CrossProduct(bp)) > 0.001f)
		{
			return false;
		}

		// Both vectors must point in opposite directions if p is between a and b
		if (ap.DotProduct(bp) > 0)
		{
			return false;
		}

		return true;
	}

	float  utils::DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
	{
		Vector2f ab{ a, b };
		Vector2f ap{ a, p };
		Vector2f abNorm{ ab.Normalized() };
		float distToA{ abNorm.DotProduct(ap) };

		// If distToA is negative, then the closest point is A
		// return the distance a, p
		if (distToA < 0)
		{
			return ap.Length();
		}
		// If distToA is > than dist(a,b) then the closest point is B
		// return the distance b, p
		float distAB{ ab.Length() };
		if (distToA > distAB)
		{
			return Vector2f{ b, p }.Length();
		}

		// Closest point is between A and B, calc intersection point
		Vector2f intersection{ abNorm.DotProduct(ap) * abNorm + Vector2f{ a } };
		return Vector2f{ p - intersection }.Length();
	}

	bool utils::IntersectRectLine(const Rectf& r, const Point2f& p1, const Point2f& p2, float& intersectMin, float& intersectMax)
	{
		// Parameters
		// input: 
		//   r: axis aligned bounding box, start and end points of line segment.
		//   p1, p2: line
		// output: 
		//   intersectMin and intersectMax: in the interval [0,1] if intersection point is on the line segment. 
		// return
		//   true if there is an intersection

		// Example of how to use
		//float min{};
		//float max{};
		//if (utils::IntersectRectLine(rect, p1, p2, min, max))
		//{
		//	Point2f intersectP1{ p1 + (Vector2f(p2) - Vector2f(p1)) * min };
		//	Point2f intersectP2{ p1 + (Vector2f(p2) - Vector2f(p1)) * max };
		//}

		// 4 floats to convert rect space to line space
		// x1: value between 0 and 1 where 0 is on p1 and 1 is on p2, <0 and >1 means intersection is not on line segment
		float x1{ (r.left - p1.x) / (p2.x - p1.x) };
		float x2{ (r.left + r.width - p1.x) / (p2.x - p1.x) };
		float y1{ (r.bottom - p1.y) / (p2.y - p1.y) };
		float y2{ (r.bottom + r.height - p1.y) / (p2.y - p1.y) };

		using std::max; using std::min;
		float tMin{ max(min(x1,x2),min(y1,y2)) };
		float tMax{ min(max(x1,x2), max(y1,y2)) };
		if (tMin > tMax)
		{
			return false;
		}
		intersectMin = tMin;
		intersectMax = tMax;
		return true;
	}
	#pragma endregion CollisionFunctionality
}