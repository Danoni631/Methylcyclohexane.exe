#include "Methylcyclohexane.h"

void InitPayloads()
{
    HANDLE GDIThread1 = CreateThread(0, 0, GDIPayloads::GDIShader1, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound1, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread1);
    HANDLE GDIThread2 = CreateThread(0, 0, GDIPayloads::GDIShader2, 0, 0, 0);
    HANDLE TextsToCrash1 = CreateThread(0, 0, GDIPayloads::Texts, 0, 0, 0);
    CreateThread(0, 0, GDIPayloads::Icons, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound2, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread2);
    HANDLE GDIThread3 = CreateThread(0, 0, GDIPayloads::GDIShader3, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound3, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread3);
    HANDLE GDIThread4 = CreateThread(0, 0, GDIPayloads::GDIShader4, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound4, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread4);
    HANDLE GDIThread5 = CreateThread(0, 0, GDIPayloads::GDIShader5, 0, 0, 0);
    CreateThread(0, 0, GDIPayloads::Icons2, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound5, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread5);
    System::EndPayload(TextsToCrash1);
    HANDLE GDIThread6 = CreateThread(0, 0, GDIPayloads::GDIShader6, 0, 0, 0);
    HANDLE TextsToCrash2 = CreateThread(0, 0, GDIPayloads::Texts2, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound6, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread6);
    CreateThread(0, 0, GDIPayloads::GDIPatBombs, 0, 0, 0);
    HANDLE GDIThread7 = CreateThread(0, 0, GDIPayloads::Pats, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound7, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread7);
    HANDLE GDIThread8 = CreateThread(0, 0, GDIPayloads::Blur, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound8, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread8);
    HANDLE GDIThread9 = CreateThread(0, 0, GDIPayloads::GDIShader7, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound9, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread9);
    HANDLE GDIThread10 = CreateThread(0, 0, GDIPayloads::GDIShader8, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound10, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread10);
    HANDLE GDIThread11 = CreateThread(0, 0, GDIPayloads::Blit, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound11, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread11);
    HANDLE GDIThread12 = CreateThread(0, 0, GDIPayloads::Blit2, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound12, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread12);
    HANDLE GDIThread13 = CreateThread(0, 0, GDIPayloads::GDIShader9, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound13, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread13);
    HANDLE GDIThread14 = CreateThread(0, 0, GDIPayloads::GDIShader10, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound14, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread14);
    HANDLE GDIThread15A = CreateThread(0, 0, GDIPayloads::Warp, 0, 0, 0);
    HANDLE GDIThread15B = CreateThread(0, 0, GDIPayloads::Pats, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound15, 0, 0, 0);
    Sleep(30000);
    System::EndPayload(GDIThread15A);
    System::EndPayload(GDIThread15B);
}

int APIENTRY wWinMain
(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // destructive version
    /*
    if
    (
        MessageBox
        (
            NULL,
            L"WARNING!!!\n\nYou are about to run a malware called Methylcyclohexane.exe, a malicious program. When you click on 'Yes', you gonna accept all responsibility when your machine will be damaged. And this program have flashing lights, strong language and loud noises. If you have epilepsy, don't run this. If you have sensibility with loud noises, turn down volume.\n\nWhen you click on 'Yes', Danoni631, SuperNaray, CrzxyMinty and NicolasBickHoff11 (the creators of this shit) don't gonna be responsabilize if your machine was damaged.\n\nClick 'Yes' to proceed, click 'No' to avoid running. This was made for educational purposes.\n\n[DATA EXPUNGED]\n\nDo you want to run this malware?",
            L"[DATA REDACTED] makes me feel pain... but its nothing to me... youll see...",
            MB_ICONWARNING | MB_YESNO
        ) != IDYES
    ) return 1;
    
    if
    (
        MessageBox
        (
            NULL,
            L"THIS IS THE LAST WARNING!!!\n\nRemember and keep on your mind the fact of this program show flashing lights, strong language, loud noises and destroy your system.\n\nDO YOU REALLY WANT TO RUN???",
            L"[DATA EXPUNGED] - Final Warning",
            MB_ICONWARNING | MB_YESNO
        ) != IDYES
    ) return 1;
    */

    if
    (
        MessageBox
        (
            NULL,
            L"WARNING!!!\n\nYou are about to run a malware called Methylcyclohexane.exe, a malicious program. You downloaded the safe version, so your computer don't gonna be damaged :D, but already have the same flashing lights, strong language and loud noises of the destructive version.\n\nDo you want to run?\n\n[DATA EXPUNGED]",
            L"[DATA REDACTED] makes me feel pain... but its nothing to me... youll see...",
            MB_ICONWARNING | MB_YESNO
        ) != IDYES
    ) return 1;

    InitPayloads();
}