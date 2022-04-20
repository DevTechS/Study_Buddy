
#include "gtest/gtest.h"
#include "StudyBuddy.h"

StudyBuddy B;

TEST(SDL_Test, SystemMetrics) {
	B.desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	B.desktopHeight = GetSystemMetrics(SM_CYSCREEN);
	EXPECT_TRUE(B.desktopWidth > 0 && B.desktopHeight > 0);
}
TEST(SDL_Test, WindowCreation) {
	B.window = SDL_CreateWindow("Study Buddy",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		B.desktopWidth, B.desktopHeight, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(B.window, &w, &h);
	EXPECT_TRUE(w == B.desktopWidth && h == B.desktopHeight);
}
TEST(SDL_Test, RendererCreation) {
	B.renderer = SDL_CreateRenderer(B.window, -1, SDL_RENDERER_ACCELERATED);
	EXPECT_TRUE(SDL_GetRenderer(B.window) == B.renderer);
}
TEST(SDL_Test, TextureLoading) {
	B.face = IMG_LoadTexture(B.renderer, "assets/Head1.png");
	int w = 0;
	int h = 0;
	SDL_QueryTexture(B.face, NULL, NULL, &w, &h);
	EXPECT_TRUE(w == 700 && h == 700);
}

TEST(Animation_Test, Idle) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Idle();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Idle();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -265 && MinHeadX > -272 && MaxHeadY < -61 && MinHeadY > -88);
}

TEST(Animation_Test, Petting) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Petting();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Petting();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -273 && MinHeadX > -277 && MaxHeadY < -34 && MinHeadY > -58);
}

TEST(Animation_Test, Wave) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Wave();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Wave();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -141 && MinHeadX > -256 && MaxHeadY < -112 && MinHeadY > -241);
}

TEST(Animation_Test, Scratch) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Scratch();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Scratch();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -276 && MinHeadX > -280 && MaxHeadY < -7 && MinHeadY > -37);
}

TEST(Animation_Test, Sleepy) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Sleepy();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Sleepy();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -235 && MinHeadX > -245 && MaxHeadY < 5 && MinHeadY > -5);
}

TEST(Animation_Test, Playful) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Playful();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Playful();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -275 && MinHeadX > -280 && MaxHeadY < 32 && MinHeadY > 21);
}

TEST(Animation_Test, Jump) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Jump();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Jump();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -113 && MinHeadX > -249 && MaxHeadY < -118 && MinHeadY > -353);
}

TEST(Animation_Test, PushClock) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.PushClock();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.PushClock();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -261 && MinHeadX > -263 && MaxHeadY < 14 && MinHeadY > 7);
}

TEST(Animation_Test, PullClock) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.PullClock();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.PullClock();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -261 && MinHeadX > -263 && MaxHeadY < 14 && MinHeadY > 7);
}

TEST(Animation_Test, Walk) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.Walk();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.Walk();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -269 && MinHeadX > -271 && MaxHeadY < -60 && MinHeadY > -80);
}

TEST(Animation_Test, WalkBack) {
	double MaxHeadX = -10000;
	double MinHeadX = 10000;
	double MaxHeadY = -10000;
	double MinHeadY = 10000;
	B.BodyX = 0;
	B.BodyY = 0;
	for (int i = 0; i < 10000; i++) {
		B.WalkBack();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;
	}
	for (int i = 0; i < 10000; i++) {
		B.WalkBack();
		B.UpdatePos();
		double BodyT_r = B.BodyT_V * PI / 180;
		double HeadOffsetX_r = cos(BodyT_r) * (B.HeadOffsetX_V - 270) - sin(BodyT_r) * (B.HeadOffsetY_V - 70);
		double HeadOffsetY_r = sin(BodyT_r) * (B.HeadOffsetX_V - 270) + cos(BodyT_r) * (B.HeadOffsetY_V - 70);

		B.HeadX = B.BodyX_V + HeadOffsetX_r;
		B.HeadY = B.BodyY_V + HeadOffsetY_r;
		B.AnimationTick++;

		//cout << B.BodyT << ", " << B.HeadX << ", " << B.HeadY << endl;

		MaxHeadX = max(MaxHeadX, B.HeadX);
		MinHeadX = min(MinHeadX, B.HeadX);
		MaxHeadY = max(MaxHeadY, B.HeadY);
		MinHeadY = min(MinHeadY, B.HeadY);
	}

	EXPECT_TRUE(MaxHeadX < -269 && MinHeadX > -271 && MaxHeadY < -60 && MinHeadY > -80);
}