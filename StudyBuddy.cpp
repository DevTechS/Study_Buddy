//
//  CEN3031 - Intro to Software Engineering
//  April 20th, 2022
//  Group 62
//  
//  Team Contributions:
//  Vishwa Krishnan (Project Manager):
//   - Front End: Developed several animations and tricks for Buddy, including sleeping, scratching, wave, eye movement, playful animation, etc. 
//   - Researched SDLand Circle CI.
//   - Contributed to all documentationand project ideation.
//   - Creative front - end efforts.
//  
//  Devin Dykstra (Scrum Master):
//   - Window Handler
//   - Render Engine
//   - Main Logic Loop
//   - Animation Rig
//   - Animation Blending / Smoothing
//   - Final Buddy Sprites
//
//  Madeleine Brewer:
//   - Helped determine and plan product idea (contributed to all documentation)
//   - Researched possibility of cross - platform product
//   - Contributed to design of buddy
//   - Wrote code for the Idle, jump, walk, walk back, push clock, and pull clock animations.
//
//
//  Dorian Karakus:
//   - Assisted in creation and planning of product idea (contributed to all documentation)
//   - Researched windows transparency functions as well as timer functions
//   - Contributed to design of buddy, timer box, and alarm clock
//   - Created both frontand back end of entire timer functionalityand interaction with user
//

#include "StudyBuddy.h"

bool StudyBuddy::MakeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}

bool StudyBuddy::MakeWindowTransparentAlpha(SDL_Window* window, COLORREF colorKey, short A) {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    return SetLayeredWindowAttributes(hWnd, colorKey, A, LWA_COLORKEY | LWA_ALPHA);
}

void StudyBuddy::renderLoop() {
    // Set background color to magenta and clear screen
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    /*
    SDL_SetRenderDrawColor(renderer2, 255, 0, 255, 255);
    SDL_RenderClear(renderer2);

    // blue square in top-left corner
    SDL_Rect rect1 = { 0 + Tick, 0, 100, 100 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);

    // red square in center of the screen
    SDL_Rect rect2 = { (desktopWidth - 100) / 2, (desktopHeight - 100) / 2, 100, 100 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect2);

    // transparent green square in center of the screen
    SDL_Rect rect3 = { (desktopWidth - 100) / 2, (desktopHeight - 100) / 4, 100, 100 };
    SDL_SetRenderDrawColor(renderer2, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer2, &rect3);
    */

    double BodyT_r = BodyT_V * PI / 180;
    double TailOffsetX_r = cos(BodyT_r) * (TailOffsetX_V + 70 - 20*sin(BodyT_r)) - sin(BodyT_r) * (TailOffsetY_V - 70);
    double TailOffsetY_r = sin(BodyT_r) * (TailOffsetX_V + 70 - 20*sin(BodyT_r)) + cos(BodyT_r) * (TailOffsetY_V - 70);

    SDL_Rect tailRect = { BodyX_V + TailOffsetX_r, BodyY_V + TailOffsetY_r, TailW, TailH };
    SDL_Point TailPivot = { TailW / 2, TailH / 4 };
    SDL_RenderCopyEx(renderer, tail, NULL, &tailRect, -45 - TailT_V, &TailPivot, SDL_FLIP_NONE);


    double BodyOffsetX_r = cos(BodyT_r) * (BodyOffsetX_V) - sin(BodyT_r) * (BodyOffsetY_V);
    double BodyOffsetY_r = sin(BodyT_r) * (BodyOffsetX_V) + cos(BodyT_r) * (BodyOffsetY_V);

    SDL_Rect bodyRect = { BodyX_V - BodyW * 3 / 4 + BodyOffsetX_r, BodyY_V - BodyH / 2 - BodyOffsetY_r, BodyW, BodyH };
    SDL_Point BodyPivot = { BodyW * 3 / 4, BodyH / 2 };
    SDL_RenderCopyEx(renderer, body, NULL, &bodyRect, BodyT_V, &BodyPivot, SDL_FLIP_HORIZONTAL);

    double HeadOffsetX_r = cos(BodyT_r) * (HeadOffsetX_V - 270) - sin(BodyT_r) * (HeadOffsetY_V - 70);
    double HeadOffsetY_r = sin(BodyT_r) * (HeadOffsetX_V - 270) + cos(BodyT_r) * (HeadOffsetY_V - 70);

    HeadX = BodyX_V + HeadOffsetX_r;
    HeadY = BodyY_V + HeadOffsetY_r;
    SDL_Rect faceRect = { HeadX - HeadSize / 2, HeadY - 75 - HeadSize / 2, HeadSize, HeadSize };
    SDL_Point HeadPivot = { 125, 200 };
    SDL_RenderCopyEx(renderer, face, NULL, &faceRect, HeadT_V, &HeadPivot, SDL_FLIP_NONE);

    double EyeXoff1 = 35 + EyeOffsetX_V;
    double EyeXoff2 = -35 + EyeOffsetX_V;
    double EyeYoff = -73 + EyeOffsetY_V;

    double HeadT_r = HeadT_V * PI / 180;
    double Xoff_r1 = cos(HeadT_r) * EyeXoff1 - sin(HeadT_r) * EyeYoff;
    double Yoff_r1 = sin(HeadT_r) * EyeXoff1 + cos(HeadT_r) * EyeYoff;
    double Xoff_r2 = cos(HeadT_r) * EyeXoff2 - sin(HeadT_r) * EyeYoff;
    double Yoff_r2 = sin(HeadT_r) * EyeXoff2 + cos(HeadT_r) * EyeYoff;

    SDL_Rect eye1Rect = { HeadX + Xoff_r1 - EyeSize / 2, HeadY + Yoff_r1 - EyeSize / 2, EyeSize, EyeSize };
    SDL_Rect eye2Rect = { HeadX + Xoff_r2 - EyeSize / 2, HeadY + Yoff_r2 - EyeSize / 2, EyeSize, EyeSize };
    switch (EyeState) {
    case 0: // default
        if (BlinkTimer < 10) {
            SDL_RenderCopyEx(renderer, eyeC, NULL, &eye1Rect, HeadT_V, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, eyeC, NULL, &eye2Rect, HeadT_V, NULL, SDL_FLIP_NONE);
        }
        else {
            SDL_RenderCopyEx(renderer, eye, NULL, &eye1Rect, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, eye, NULL, &eye2Rect, 0, NULL, SDL_FLIP_NONE);
        }
        break;
    case 1: // happy
        SDL_RenderCopyEx(renderer, eyeH, NULL, &eye1Rect, HeadT_V, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, eyeH, NULL, &eye2Rect, HeadT_V, NULL, SDL_FLIP_NONE);
        break;
    case 2: // closed
        SDL_RenderCopyEx(renderer, eyeC, NULL, &eye1Rect, HeadT_V, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, eyeC, NULL, &eye2Rect, HeadT_V, NULL, SDL_FLIP_NONE);
        break;
    }

    SDL_Rect mouthRect = { HeadX - mouthW / 2 + MouthOffsetX_V, HeadY - 14 - mouthH / 2 + MouthOffsetY_V, mouthW, mouthH };
    SDL_Point MouthPivot = { mouthW / 2, mouthH / 2 + 14 };
    switch (MouthState) {
    case 0: // default (happy)
        SDL_RenderCopyEx(renderer, mouth, NULL, &mouthRect, HeadT_V, &MouthPivot, SDL_FLIP_NONE);
        break;
    case 1: // tounge out
        SDL_RenderCopyEx(renderer, mouthT, NULL, &mouthRect, HeadT_V, &MouthPivot, SDL_FLIP_NONE);
        break;
    case 2: // neutral
        SDL_RenderCopyEx(renderer, mouthS, NULL, &mouthRect, HeadT_V, &MouthPivot, SDL_FLIP_NONE);
        break;
    }

    SDL_Rect Paw0Rect = { BodyX_V - PawW / 2 - 240 + Paw0OffsetX_V, BodyY_V - PawH / 2 + 120 + Paw0OffsetY_V, PawW, PawH };
    SDL_Rect Paw1Rect = { BodyX_V - PawW / 2 - 230 + Paw1OffsetX_V, BodyY_V - PawH / 2 + 120 + Paw1OffsetY_V, PawW, PawH };
    SDL_Rect Paw2Rect = { BodyX_V - PawW / 2 + 30 + Paw2OffsetX_V, BodyY_V - PawH / 2 + 120 + Paw2OffsetY_V, PawW, PawH };
    SDL_Rect Paw3Rect = { BodyX_V - PawW / 2 + 40 + Paw3OffsetX_V, BodyY_V - PawH / 2 + 120 + Paw3OffsetY_V, PawW, PawH };
    switch (Paw0State) {
    case 0: // down
        SDL_RenderCopyEx(renderer, pawDown, NULL, &Paw0Rect, Paw0T_V, NULL, SDL_FLIP_NONE);
        break;
    case 1: // up
        SDL_RenderCopyEx(renderer, pawUp, NULL, &Paw0Rect, Paw0T_V, NULL, SDL_FLIP_NONE);
        break;
    }
    switch (Paw1State) {
    case 0:
        SDL_RenderCopyEx(renderer, pawDown, NULL, &Paw1Rect, Paw1T_V, NULL, SDL_FLIP_NONE);
        break;
    case 1:
        SDL_RenderCopyEx(renderer, pawUp, NULL, &Paw1Rect, Paw1T_V, NULL, SDL_FLIP_NONE);
        break;
    }
    switch (Paw2State) {
    case 0:
        SDL_RenderCopyEx(renderer, pawDown, NULL, &Paw2Rect, Paw2T_V, NULL, SDL_FLIP_NONE);
        break;
    case 1:
        SDL_RenderCopyEx(renderer, pawUp, NULL, &Paw2Rect, Paw2T_V, NULL, SDL_FLIP_NONE);
        break;
    }
    switch (Paw3State) {
    case 0:
        SDL_RenderCopyEx(renderer, pawDown, NULL, &Paw3Rect, Paw3T_V, NULL, SDL_FLIP_NONE);
        break;
    case 1:
        SDL_RenderCopyEx(renderer, pawUp, NULL, &Paw3Rect, Paw3T_V, NULL, SDL_FLIP_NONE);
        break;
    }

    SDL_Rect ClockRect = { ClockX_V, ClockY_V, ClockW, ClockH };
    SDL_RenderCopyEx(renderer, alarmclock, NULL, &ClockRect, ClockT_V, NULL, SDL_FLIP_NONE);

    if (ShowTimerWindow) {
        SDL_Rect TimerWindowRect = { TimerWindowX, TimerWindowY, TimerWindowW, TimerWindowH };
        SDL_RenderCopyEx(renderer, timerWindow, NULL, &TimerWindowRect, 0, NULL, SDL_FLIP_NONE);

        SDL_Rect HourRect = { TimerWindowX + 230, TimerWindowY + 110, 200, 200 };
        SDL_RenderCopyEx(renderer, digits[Hours%10], NULL, &HourRect, 0, NULL, SDL_FLIP_NONE);

        SDL_Rect MinHRect = { TimerWindowX + 580, TimerWindowY + 110, 200, 200 };
        SDL_Rect MinLRect = { TimerWindowX + 650, TimerWindowY + 110, 200, 200 };
        SDL_RenderCopyEx(renderer, digits[Minutes/10], NULL, &MinHRect, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, digits[Minutes%10], NULL, &MinLRect, 0, NULL, SDL_FLIP_NONE);
    }


    // Add window transparency (Magenta will be transparent)
    MakeWindowTransparent(window, RGB(255, 0, 255));
    //MakeWindowTransparentAlpha(window2, RGB(255, 0, 255), 100);

    SDL_RenderPresent(renderer);
    //SDL_RenderPresent(renderer2);
}

void StudyBuddy::UpdatePos() {
    BodyX_V += (BodyX - BodyX_V) * 0.25;
    BodyY_V += (BodyY - BodyY_V) * 0.25;
    BodyOffsetX_V += (BodyOffsetX - BodyOffsetX_V)*0.25;
    BodyOffsetY_V += (BodyOffsetY - BodyOffsetY_V)*0.25;
    BodyT_V += (BodyT - BodyT_V)*0.25;

    TailOffsetX_V += (TailOffsetX - TailOffsetX_V)*0.25;
    TailOffsetY_V += (TailOffsetY - TailOffsetY_V)*0.25;
    TailT_V += (TailT - TailT_V)*0.50;

    HeadOffsetX_V += (HeadOffsetX - HeadOffsetX_V)*0.25;
    HeadOffsetY_V += (HeadOffsetY - HeadOffsetY_V)*0.25;
    HeadT_V += (HeadT - HeadT_V)*0.25;

    EyeOffsetX_V += (EyeOffsetX - EyeOffsetX_V)*0.25;
    EyeOffsetY_V += (EyeOffsetY - EyeOffsetY_V)*0.25;

    MouthOffsetX_V += (MouthOffsetX - MouthOffsetX_V)*0.25;
    MouthOffsetY_V += (MouthOffsetY - MouthOffsetY_V)*0.25;

    Paw0OffsetX_V += (Paw0OffsetX - Paw0OffsetX_V)*0.25;
    Paw0OffsetY_V += (Paw0OffsetY - Paw0OffsetY_V)*0.25;
    Paw0T_V += (Paw0T - Paw0T_V)*0.25;

    Paw1OffsetX_V += (Paw1OffsetX - Paw1OffsetX_V)*0.25;
    Paw1OffsetY_V += (Paw1OffsetY - Paw1OffsetY_V)*0.25;
    Paw1T_V += (Paw1T - Paw1T_V)*0.25;

    Paw2OffsetX_V += (Paw2OffsetX - Paw2OffsetX_V)*0.25;
    Paw2OffsetY_V += (Paw2OffsetY - Paw2OffsetY_V)*0.25;
    Paw2T_V += (Paw2T - Paw2T_V)*0.25;

    Paw3OffsetX_V += (Paw3OffsetX - Paw3OffsetX_V) * 0.25;
    Paw3OffsetY_V += (Paw3OffsetY - Paw3OffsetY_V) * 0.25;
    Paw3T_V += (Paw3T - Paw3T_V) * 0.25;

    ClockX_V += (ClockX - ClockX_V) * 0.25;
    ClockY_V += (ClockY - ClockY_V) * 0.25;
    ClockT_V += (ClockT - ClockT_V) * 0.25;
}

void StudyBuddy::Idle() {
    BodyOffsetX = 0;
    BodyOffsetY = 0;
    BodyT = 1 + 2 * sin(AnimationTick / 40.0);

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 15 + 15 * sin(AnimationTick / 40.0);

    HeadOffsetX = 0;
    HeadOffsetY = 5 * sin(AnimationTick / 80.0);
    HeadT = 5 * sin(AnimationTick / 60.0);

    EyeOffsetX = 10 * (double)(mouse.x - HeadX) / desktopWidth;
    EyeOffsetY = 10 * (double)(mouse.y - HeadY) / desktopHeight;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = 0;
    Paw0OffsetY = 0;
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 0;
    Paw1OffsetY = 0;
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = 0;
    Paw2OffsetY = 0;
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 0;
    MouthState = 0;
}

void StudyBuddy::Petting() {
    BodyOffsetX = 0;
    BodyOffsetY = 0;
    BodyT = -5 + sin(AnimationTick / 10.0);

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 15 + 15 * sin(PetCounter / 40.0 + AnimationTick / 40.0);

    HeadOffsetX = 0;
    HeadOffsetY = 8 * sin(AnimationTick / 15.0);
    HeadT = 5 * sin(AnimationTick / 10.0);

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = 0;
    Paw0OffsetY = 2 * sin(PetCounter / 40.0 + AnimationTick / 40.0);
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 0;
    Paw1OffsetY = 2 * cos(PetCounter / 40.0 + AnimationTick / 40.0);
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = 0;
    Paw2OffsetY = 0;
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 1;
    MouthState = 1;
}

void StudyBuddy::Wave() {
    BodyOffsetX = 0;
    BodyOffsetY = 0;
    BodyT = 45 * sqrt(abs(sin(AnimationTick / 40.0)));

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 30 * sin(AnimationTick / 4.0);

    HeadOffsetX = 0;
    HeadOffsetY = 0;
    HeadT = 15 * sqrt(abs(sin(AnimationTick / 40.0)));

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -25 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0OffsetY = -150 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0T = -80 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0State = 0;

    Paw1OffsetX = 150 + 50 * sin(AnimationTick / 2.0) + 50 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw1OffsetY = -270 + 10 * sin(AnimationTick / 2.0) - 100 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw1T = 25;
    Paw1State = 1;

    Paw2OffsetX = 0;
    Paw2OffsetY = 0;
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = abs(sin(AnimationTick / 40.0)) > 0.5;
    MouthState = 0;
}

void StudyBuddy::Scratch()
{
    /*
    BodyOffsetX = 0;
    BodyOffsetY = 0;
    BodyT = -20 + 2 * sin(AnimationTick / 200.0);
    */

    //BodyOffsetX = 150 + 50 * sin(AnimationTick / 2.0) + 50 * sqrt(abs(sin(AnimationTick / 40.0)));
    //BodyOffsetY = 270 + 10 * sin(AnimationTick / 2.0) - 100 * sqrt(abs(sin(AnimationTick / 40.0)));
    BodyT = -10 - sin(AnimationTick / 80.0);

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 10 * sin(AnimationTick / 20.0);

    HeadOffsetX = 0;
    HeadOffsetY = 10 * sin(AnimationTick / 80.0);
    HeadT = 20;

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = 0;
    Paw0OffsetY = 0;
    Paw0T = 0;
    Paw0State = 0;


    Paw1OffsetX = 0;
    Paw1OffsetY = 0;
    Paw1T = 0;
    Paw1State = 0;


    Paw2OffsetX = -200 + 50 * sin(AnimationTick / 4.0) + 50 * sqrt(abs(sin(AnimationTick / 60.0)));
    Paw2OffsetY = -270;
    Paw2T = 25;
    Paw2State = 0;


    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 1;
    MouthState = 2;
}

void StudyBuddy::Sleepy()
{
    BodyOffsetX = 0;
    BodyOffsetY = -60 + 5 * sin(AnimationTick / 150.0);
    BodyT = 0;

    TailOffsetX = 0;
    TailOffsetY = 50;
    TailT = 10 * sin(AnimationTick / 20.0);

    HeadOffsetX = -5 * sin(AnimationTick / 80.0) + 30;
    HeadOffsetY = 70 - 5 * sin(AnimationTick / 150.0);//-10 * sin(AnimationTick / 80.0);
    HeadT = -40;

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = 0;
    Paw0OffsetY = 0;
    Paw0T = 0;
    Paw0State = 0;


    Paw1OffsetX = 0;
    Paw1OffsetY = 0;
    Paw1T = 0;
    Paw1State = 0;


    Paw2OffsetX = 0;
    Paw2OffsetY = 0;
    Paw2T = 0;
    Paw2State = 0;


    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 2;
    MouthState = 2;
}

void StudyBuddy::Playful() {
    BodyOffsetX = 0;
    BodyOffsetY = 0;
    BodyT = -20;

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 100 + 15 * sin(AnimationTick / 5.0);

    HeadOffsetX = 0;
    HeadOffsetY = 5 * sin(AnimationTick / 80.0);
    HeadT = 5 * sin(AnimationTick / 60.0);

    EyeOffsetX = 10 * (double)(mouse.x - HeadX) / desktopWidth;
    EyeOffsetY = 10 * (double)(mouse.y - HeadY) / desktopHeight;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = 0;
    Paw0OffsetY = 0;
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 0;
    Paw1OffsetY = 0;
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = 0;
    Paw2OffsetY = 0;
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 0;
    Paw3OffsetY = 0;
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 0;
    MouthState = 1;
}

void StudyBuddy::Jump() {
    BodyOffsetX = 100 * abs(sin(AnimationTick / 40.0));
    BodyOffsetY = 100 * abs(sin(AnimationTick / 40.0));
    BodyT = 45 * sqrt(abs(sin(AnimationTick / 40.0)));

    TailOffsetX = -90 * abs(sin(AnimationTick / 40.0)) + 5;
    TailOffsetY = -90 * sqrt(abs(sin(AnimationTick / 40.0)));
    TailT = 10 * sin(AnimationTick / 10.0);

    HeadOffsetX = -70 * abs(sin(AnimationTick / 40.0)) + 10;
    HeadOffsetY = -100 * abs(sin(AnimationTick / 40.0));
    HeadT = 15 * sqrt(abs(sin(AnimationTick / 40.0)));

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -45 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0OffsetY = -350 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0T = -80 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw0State = 0;

    Paw1OffsetX = -25 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw1OffsetY = -300 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw1T = -80 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw1State = 0;

    Paw2OffsetX = -45 * sqrt(abs(sin(AnimationTick / 40.0)));;
    Paw2OffsetY = -140 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw2T = -60 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw2State = 0;

    Paw3OffsetX = -25 * sqrt(abs(sin(AnimationTick / 40.0)));;
    Paw3OffsetY = -120 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw3T = -60 * sqrt(abs(sin(AnimationTick / 40.0)));
    Paw3State = 0;

    EyeState = abs(sin(AnimationTick / 40.0)) > 0.5;
    MouthState = abs(sin(AnimationTick / 40.0)) > 0.5;
}

void StudyBuddy::PushClock() {

    BodyOffsetX = 0;
    BodyOffsetY = 5 * sin(AnimationTick / 10.0);
    BodyT = -10;

    TailOffsetX = 0;
    TailOffsetY = 30;
    TailT = 15 + 15 * sin(AnimationTick / 10.0);

    HeadOffsetX = 10;
    HeadOffsetY = 35 + 3 * sin(AnimationTick / 10.0);
    HeadT = -40;

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -30 * sin(AnimationTick / 20.0);
    Paw0OffsetY = -10 * cos(AnimationTick / 20.0);
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 30 * sin(AnimationTick / 20.0);
    Paw1OffsetY = 10 * cos(AnimationTick / 20.0);
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = -30 * sin(AnimationTick / 20.0);
    Paw2OffsetY = -10 * cos(AnimationTick / 20.0);
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 30 * sin(AnimationTick / 20.0);
    Paw3OffsetY = 10 * cos(AnimationTick / 20.0);
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 1;
    MouthState = 2;
}

void StudyBuddy::PullClock() {

    BodyOffsetX = 0;
    BodyOffsetY = 5 * sin(AnimationTick / 10.0);
    BodyT = -10;

    TailOffsetX = 0;
    TailOffsetY = 30;
    TailT = 15 + 15 * sin(AnimationTick / 10.0);

    HeadOffsetX = 10;
    HeadOffsetY = 35 + 3 * sin(AnimationTick / 10.0);
    HeadT = -40;

    EyeOffsetX = 0;
    EyeOffsetY = 0;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -30 * cos(AnimationTick / 20.0);
    Paw0OffsetY = -10 * sin(AnimationTick / 20.0);
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 30 * cos(AnimationTick / 20.0);
    Paw1OffsetY = 10 * sin(AnimationTick / 20.0);
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = -30 * cos(AnimationTick / 20.0);
    Paw2OffsetY = -10 * sin(AnimationTick / 20.0);
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 30 * cos(AnimationTick / 20.0);
    Paw3OffsetY = 10 * sin(AnimationTick / 20.0);
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 1;
    MouthState = 0;
}

void StudyBuddy::Walk() {

    BodyOffsetX = 0;
    BodyOffsetY = 5 * sin(AnimationTick / 10.0);
    BodyT = 0;

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 15 + 15 * sin(AnimationTick / 10.0);

    HeadOffsetX = 0;
    HeadOffsetY = -10 * sin(AnimationTick / 10.0);
    HeadT = 5 * sin(AnimationTick / 60.0);

    EyeOffsetX = 10 * (double)(mouse.x - HeadX) / desktopWidth;
    EyeOffsetY = 10 * (double)(mouse.y - HeadY) / desktopHeight;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -30 * sin(AnimationTick / 10.0);
    Paw0OffsetY = -10 * cos(AnimationTick / 10.0);
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 30 * sin(AnimationTick / 10.0);
    Paw1OffsetY = 10 * cos(AnimationTick / 10.0);
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = -30 * sin(AnimationTick / 10.0);
    Paw2OffsetY = -10 * cos(AnimationTick / 10.0);
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 30 * sin(AnimationTick / 10.0);
    Paw3OffsetY = 10 * cos(AnimationTick / 10.0);
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 0;
    MouthState = 0;
}

void StudyBuddy::WalkBack() {

    BodyOffsetX = 0;
    BodyOffsetY = 5 * sin(AnimationTick / 10.0);
    BodyT = 0;

    TailOffsetX = 0;
    TailOffsetY = 0;
    TailT = 15 + 15 * sin(AnimationTick / 10.0);

    HeadOffsetX = 0;
    HeadOffsetY = -10 * sin(AnimationTick / 10.0);
    HeadT = 5 * sin(AnimationTick / 60.0);

    EyeOffsetX = 10 * (double)(mouse.x - HeadX) / desktopWidth;
    EyeOffsetY = 10 * (double)(mouse.y - HeadY) / desktopHeight;

    MouthOffsetX = 0;
    MouthOffsetY = 0;

    Paw0OffsetX = -30 * cos(AnimationTick / 10.0);
    Paw0OffsetY = -10 * sin(AnimationTick / 10.0);
    Paw0T = 0;
    Paw0State = 0;

    Paw1OffsetX = 30 * cos(AnimationTick / 10.0);
    Paw1OffsetY = 10 * sin(AnimationTick / 10.0);
    Paw1T = 0;
    Paw1State = 0;

    Paw2OffsetX = -30 * cos(AnimationTick / 10.0);
    Paw2OffsetY = -10 * sin(AnimationTick / 10.0);
    Paw2T = 0;
    Paw2State = 0;

    Paw3OffsetX = 30 * cos(AnimationTick / 10.0);
    Paw3OffsetY = 10 * sin(AnimationTick / 10.0);
    Paw3T = 0;
    Paw3State = 0;

    EyeState = 0;
    MouthState = 0;
}

int StudyBuddy::StartBuddy() {

    window = SDL_CreateWindow("Study Buddy",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        desktopWidth, desktopHeight, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);
    /*
    window2 = SDL_CreateWindow("Translucent Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        desktopWidth, desktopHeight, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);
    */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED);
    
    // Load PNGs
    face = IMG_LoadTexture(renderer, "assets/Head1.png");
    eye = IMG_LoadTexture(renderer, "assets/Eye0.png");
    eyeH = IMG_LoadTexture(renderer, "assets/Eye1.png");
    eyeC = IMG_LoadTexture(renderer, "assets/Eye2.png");
    mouth = IMG_LoadTexture(renderer, "assets/Mouth0.png");
    mouthT = IMG_LoadTexture(renderer, "assets/Mouth1.png");
    mouthS = IMG_LoadTexture(renderer, "assets/Mouth2.png");
    body = IMG_LoadTexture(renderer, "assets/Body.png");
    pawDown = IMG_LoadTexture(renderer, "assets/Paw0.png");
    pawUp = IMG_LoadTexture(renderer, "assets/Paw1.png");
    tail = IMG_LoadTexture(renderer, "assets/Tail.png");
    alarmclock = IMG_LoadTexture(renderer, "assets/alarmclock.png");
    timerWindow = IMG_LoadTexture(renderer, "assets/TimerWindow.png");
    digits[0] = IMG_LoadTexture(renderer, "assets/0.png");
    digits[1] = IMG_LoadTexture(renderer, "assets/1.png");
    digits[2] = IMG_LoadTexture(renderer, "assets/2.png");
    digits[3] = IMG_LoadTexture(renderer, "assets/3.png");
    digits[4] = IMG_LoadTexture(renderer, "assets/4.png");
    digits[5] = IMG_LoadTexture(renderer, "assets/5.png");
    digits[6] = IMG_LoadTexture(renderer, "assets/6.png");
    digits[7] = IMG_LoadTexture(renderer, "assets/7.png");
    digits[8] = IMG_LoadTexture(renderer, "assets/8.png");
    digits[9] = IMG_LoadTexture(renderer, "assets/9.png");

    /*
    POINT p;
    for (int i = 0; i < 1000; i++) {
        GetCursorPos(&p);
        cout << p.x << ", " << p.y << endl;
        // found here https://stackoverflow.com/questions/18318911/detect-if-mouse-button-is-down
        // about winmain https://stackoverflow.com/questions/13871617/winmain-and-main-in-c-extended
        if (((GetKeyState(VK_LBUTTON) & 0x8000) != 0))
        {
            keybd_event(VkKeyScan('a'), 0, 0, 0);
        }
        else {
            cout << "not ";
        }
        cout << "pressed: " << GetKeyState(VK_LBUTTON) << endl;
        Sleep(30);
    }
    */

    std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();

    bool quit = false;
    while (!quit) {
        Oldmouse = mouse;
        GetCursorPos(&mouse);

        if (!--BlinkTimer) {
            if (rand()%10 < 1) {
                BlinkTimer = rand() % 120 + 40;
                fidgeting = 1;
            }else {
                BlinkTimer = rand() % 60 + 180;
                fidgeting = 0;
            }
        }

        switch (Stage) {
        case 0:
            PushClock();
            BodyX -= 2;
            ClockT = -10;
            ClockX -= 2;
            if (ClockX < desktopWidth - 650) {
                ClockT = 0;
                Tick = 0;
                Stage = 1;
            }
            break;
        case 1:
            WalkBack();
            BodyX += 2;
            if (Tick > 50) {
                Stage = 2;
                Tick = 0;
                AnimationTick = 0;
            }
            break;
        case 2:
            Wave();
            if (Tick > 125) {
                Stage = 3;
                InactivityTimer = 0;
            }
            break;
        case 3:
            clickingClock = mousePressed && mouse.x > ClockX && mouse.x < ClockX + ClockW && mouse.y > ClockY && mouse.y < ClockY + ClockH; // check bounds for clock and timer window
            clickingTimerWindow = mousePressed && mouse.x > TimerWindowX && mouse.x < TimerWindowX + TimerWindowW && mouse.y > TimerWindowY && mouse.y < TimerWindowY + TimerWindowH;

            if (clickingClock) {
                ShowTimerWindow = 1;
            }

            if (clickingTimerWindow && ButtonTimer == 0) {

                int relY = mouse.y - TimerWindowY;
                int relX = mouse.x - TimerWindowX;
                if (relX > 784 && relY < 71) {
                    ShowTimerWindow = 0;
                    mousePressed = 0;
                }
                else if (relX > 134 && relY > 141 && relX < 188 && relY < 202) { // hours up
                    ButtonTimer = 50;
                    Hours++;
                    if (Hours > 9) {
                        Hours = 0;
                    }
                }
                else if (relX > 465 && relY > 140 && relX < 519 && relY < 200) { // minutes up
                    ButtonTimer = 3;
                    Minutes++;
                    if (Minutes > 59) { // rollover
                        Minutes = 0;
                        Hours++;
                        if (Hours > 9) {
                            Hours = 0;
                        }
                    }
                }
                else if (relX > 134 && relY > 217 && relX < 188 && relY < 274) { // hours down
                    ButtonTimer = 50;
                    Hours--;
                    if (Hours < 0) {
                        Hours = 9;
                    }
                }
                else if (relX > 465 && relY > 216 && relX < 519 && relY < 274) { // minutes down
                    ButtonTimer = 3;
                    Minutes--;
                    if (Minutes < 0) { // rollover
                        Minutes = 59;
                        Hours--;
                        if (Hours < 0) {
                            Hours = 9;
                        }
                    }
                }
                else if (relX > 312 && relY > 319 && relX < 568 && relY < 363) { // X button
                    ShowTimerWindow = 0;
                    mousePressed = 0;
                    Tick = 0;
                    Stage = 4;
                }
            }
            else {
                // slows hour ticking if holding button
                if (!mousePressed) {
                    ButtonTimer = 0;
                }
                else {
                    ButtonTimer--;
                }
            }

            if (mousePressed && TrickCounter == 0 && !clickingClock && !clickingTimerWindow) {
                InactivityTimer = 0;
                ShowTimerWindow = 0;
                PetCounter += sqrt(pow(Oldmouse.x - mouse.x, 2) + pow(Oldmouse.y - mouse.y, 2));
                PetLevel += sqrt(pow(Oldmouse.x - mouse.x, 2) + pow(Oldmouse.y - mouse.y, 2));
                PetLevel *= 0.99;
                TrickCounter = 0;
                Petting();
            }
            else {
                if (PetLevel > 1000) {
                    Playful();
                    if (TrickCounter == 60) {
                        AnimationTick = 0;
                        if (mouse.y < desktopHeight / 2) {
                            Trick = 0;
                        }
                        else {
                            Trick = 1;
                        }
                    }
                    if (TrickCounter++ > 60) {
                        switch (Trick) {
                        case 0:
                            Jump();
                            if (AnimationTick == 125) {
                                PetLevel = 0;
                                TrickCounter = 0;
                            }
                            break;
                        case 1:
                            //rollover
                            if (AnimationTick == 125) {
                                PetLevel = 0;
                                TrickCounter = 0;
                            }
                            break;
                        }
                    }
                }
                else if (InactivityTimer > 2.5*60*60) {
                    Sleepy();
                }
                else {
                    PetLevel = 0;
                    PetCounter = 0;
                    if (fidgeting) {
                        Scratch();
                    }
                    else {
                        Idle();
                    }
                }
            }
            break;
        case 4:
            Walk();
            BodyX -= 2;
            if (Tick > 50) {
                Stage = 5;
                Tick = 0;
                AnimationTick = 0;
            }
            break;
        case 5:
            PullClock();
            BodyX += 2;
            ClockT = 10;
            ClockX += 2;
            if (ClockX > desktopWidth + 60) {
                ClockT = 0;
                Tick = 0;
                Stage = 6;
                TimerStartTime = std::chrono::system_clock::now();
            }
            break;
        case 6:
            if (TimerStartTime + std::chrono::hours(Hours) + std::chrono::minutes(Minutes) < std::chrono::system_clock::now()) {
                Stage = 0;
            }
            else {
                std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1000)); // periodically check for SDL events to prevent Not responding error
            }
            break;
        }

        if (Stage != 6) {
            UpdatePos();
            renderLoop();
        }

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePressed = 1;
                //mousePress(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mousePressed = 0;
                //mousePress(event.button);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mousePressed = 1;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                ShowTimerWindow = 0;
                mousePressed = 0;
                break;
            }
        }

        std::this_thread::sleep_until(StartTime + std::chrono::milliseconds(16));
        //cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch() - StartTime.time_since_epoch()).count() << endl;
        StartTime = std::chrono::system_clock::now();

        Tick++;
        AnimationTick++;
        InactivityTimer++;
    }

    //clear memory
    SDL_DestroyTexture(face);
    SDL_DestroyTexture(eye);
    SDL_DestroyTexture(eyeH);
    SDL_DestroyTexture(eyeC);
    SDL_DestroyTexture(mouth);
    SDL_DestroyTexture(mouthT);
    SDL_DestroyTexture(mouthS);
    SDL_DestroyTexture(body);
    SDL_DestroyTexture(pawDown);
    SDL_DestroyTexture(pawUp);
    SDL_DestroyTexture(tail);
    SDL_DestroyTexture(alarmclock);
    SDL_DestroyTexture(timerWindow);
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(digits[i]);
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int main(int argc, char* argv[]) {
    StudyBuddy Buddy;
    return Buddy.StartBuddy();
}