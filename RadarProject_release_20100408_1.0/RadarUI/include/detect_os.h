#ifndef C_DETECT_OS_H
#define C_DETECT_OS_H

/*!
  \file
  \brief “®ìOS‚ÌŒŸo

  \author Satofumi KAMIMURA

  $Id: detect_os.h 130 2008-07-25 06:00:54Z satofumi $
*/

#if defined _MSC_VER || defined __CYGWIN__ || defined __MINGW32__
#define WINDOWS_OS

#if defined _MSC_VER
#define MSC
#elif defined __CYGWIN__
#define Cygwin
#elif defined __MINGW32__
#define MinGW
#endif

#elif defined __linux__
#define LINUX_OS

#else
// ŒŸo‚Å‚«‚È‚¢‚Æ‚«‚ğAMac ˆµ‚¢‚É‚µ‚Ä‚µ‚Ü‚¤
#define MAC_OS
#endif

#endif /* !C_DETECT_OS_H */
