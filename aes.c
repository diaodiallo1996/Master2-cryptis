#include "aes_dlc.h"


/******************aes_table.c*************************************/

 const unsigned char invSBOX[256] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

 const unsigned long int mul9[256] =
 {
  0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,
  0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,
  0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,
  0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,
  0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,
  0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,
  0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,
  0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,
  0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,
  0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,
  0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,
  0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,
  0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,
  0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,
  0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,
  0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46
 };

  const unsigned long int mulb[256] =
 {
  0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,
  0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,
  0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,
  0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,
  0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,
  0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,
  0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,
  0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,
  0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,
  0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,
  0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,
  0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,
  0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,
  0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,
  0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,
  0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3
 };

  const unsigned long int muld[256]=
 {
  0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,
  0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,
  0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,
  0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,
  0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,
  0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,
  0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,
  0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,
  0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,
  0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,
  0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,
  0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,
  0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,
  0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,
  0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,
  0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97
 };
  const unsigned long int mule[256] =
 {
  0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,
  0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,
  0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,
  0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,
  0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,
  0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,
  0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,
  0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,
  0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,
  0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,
  0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,
  0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,
  0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,
  0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,
  0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,
  0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d
 };

 const unsigned long int MatriceMixcolum_inverse[4][4] =
{   {0x0e , 0x0b , 0x0d , 0x09},
    {0x09 , 0x0e , 0x0b , 0x0d},
    {0x0d , 0x09 , 0x0e , 0x0b},
    {0x0b , 0x0d , 0x09 , 0x0e}
};

 const unsigned long int mul3[256] =
  { 0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11,
    0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21,
    0x60, 0x63, 0x66, 0x65, 0x6c, 0x6f, 0x6a, 0x69, 0x78, 0x7b, 0x7e, 0x7d, 0x74, 0x77, 0x72, 0x71,
    0x50, 0x53, 0x56, 0x55, 0x5c, 0x5f, 0x5a, 0x59, 0x48, 0x4b, 0x4e, 0x4d, 0x44, 0x47, 0x42, 0x41,
    0xc0, 0xc3, 0xc6, 0xc5, 0xcc, 0xcf, 0xca, 0xc9, 0xd8, 0xdb, 0xde, 0xdd, 0xd4, 0xd7, 0xd2, 0xd1,
    0xf0, 0xf3, 0xf6, 0xf5, 0xfc, 0xff, 0xfa, 0xf9, 0xe8, 0xeb, 0xee, 0xed, 0xe4, 0xe7, 0xe2, 0xe1,
    0xa0, 0xa3, 0xa6, 0xa5, 0xac, 0xaf, 0xaa, 0xa9, 0xb8, 0xbb, 0xbe, 0xbd, 0xb4, 0xb7, 0xb2, 0xb1,
    0x90, 0x93, 0x96, 0x95, 0x9c, 0x9f, 0x9a, 0x99, 0x88, 0x8b, 0x8e, 0x8d, 0x84, 0x87, 0x82, 0x81,
    0x9b, 0x98, 0x9d, 0x9e, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8f, 0x8c, 0x89, 0x8a,
    0xab, 0xa8, 0xad, 0xae, 0xa7, 0xa4, 0xa1, 0xa2, 0xb3, 0xb0, 0xb5, 0xb6, 0xbf, 0xbc, 0xb9, 0xba,
    0xfb, 0xf8, 0xfd, 0xfe, 0xf7, 0xf4, 0xf1, 0xf2, 0xe3, 0xe0, 0xe5, 0xe6, 0xef, 0xec, 0xe9, 0xea,
    0xcb, 0xc8, 0xcd, 0xce, 0xc7, 0xc4, 0xc1, 0xc2, 0xd3, 0xd0, 0xd5, 0xd6, 0xdf, 0xdc, 0xd9, 0xda,
    0x5b, 0x58, 0x5d, 0x5e, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4f, 0x4c, 0x49, 0x4a,
    0x6b, 0x68, 0x6d, 0x6e, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7f, 0x7c, 0x79, 0x7a,
    0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a,
    0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a, 
  };

 const unsigned long int mul2[256] =
{ 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a ,0x0c , 0x0e, 0x10 ,0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
  0x20, 0x22, 0x24, 0x26, 0x28, 0x2a ,0x2c , 0x2e, 0x30 ,0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e,
  0x40, 0x42, 0x44, 0x46, 0x48, 0x4a ,0x4c , 0x4e, 0x50 ,0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e,
  0x60, 0x62, 0x64, 0x66, 0x68, 0x6a ,0x6c , 0x6e, 0x70 ,0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
  0x80, 0x82, 0x84, 0x86, 0x88, 0x8a ,0x8c , 0x8e, 0x90 ,0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e,
  0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa ,0xac , 0xae, 0xb0 ,0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe,
  0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca ,0xcc , 0xce, 0xd0 ,0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde,
  0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea ,0xec , 0xee, 0xf0 ,0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe,
  0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11 ,0x17 , 0x15, 0x0b ,0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05,
  0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31 ,0x37 , 0x35, 0x2b ,0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25,
  0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51 ,0x57 , 0x55, 0x4b ,0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45,
  0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71 ,0x77 , 0x75, 0x6b ,0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65,
  0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91 ,0x97 , 0x95, 0x8b ,0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85,
  0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1 ,0xb7 , 0xb5, 0xab ,0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5,
  0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1 ,0xd7 , 0xd5, 0xcb ,0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5,
  0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1 ,0xf7 , 0xf5, 0xeb ,0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5
};

 const unsigned long int MatriceMixcolum[4][4] =
{   {0x02 , 0x03 , 0x01 , 0x01},
    {0x01 , 0x02 , 0x03 , 0x01},
    {0x01 , 0x01 , 0x02 , 0x03},
    {0x03 , 0x01 , 0x01 , 0x02}
};

 const unsigned long int RCON[11] ={ 0x8d , 0x01 , 0x02 , 0x04, 0x08 , 0x10 , 0x20 ,0x40 , 0x80 , 0x1b  , 0x36 };
 const unsigned long int SBOX_AES[256] =
{
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};


void paddingExtractor(char * filename){
    FILE *fic= fopen(filename , "rb");
    char *buffer;
    fseek(fic, 0L, SEEK_END);
    unsigned long fileLen = ftell(fic);
    fseek(fic, 0L, SEEK_SET);
    buffer = calloc(fileLen+1, sizeof(char));
    fread(buffer, fileLen,1,fic);
    fclose(fic);
    buffer[fileLen]='\0';
    int j = fileLen;
    for(int i= fileLen-1; i > fileLen -16; i--){
        if (buffer[i]!=0){
            j=i;
            break;
        }
    }
    // buffer[j]='\0';
    fic= fopen(filename , "wb");
    fwrite(buffer,j+1, 1, fic);
    fclose(fic);
}

/*******************fonction_commune*******************/

int expension_cle_rsa( unsigned long int k[][4] , unsigned long int **w ){
	unsigned long int i , j ;

	for (  j = 0; j <=3; ++j) //pour tout les colonnes 
	{
		for ( i = 0; i <=3 ; ++i) // pour tout les lignes 
		{
			w[j][i]=k[j][i];
		}
	}
	for ( j =4 ; j < 44; ++j )
	{	
		if ( j%4 == 0 )
		{
			w[0][j]=w[0][j-4]^SBOX_AES[ (int)w[1][j-1] ]^RCON[j/4];
			
			for ( i = 1; i <4; ++i)
			{
				w[i][j]=w[i][j-4]^SBOX_AES[ (int)w[(i+1)%4 ][j-1] ];
			}
		}
		else {
			for (i=0 ; i<4 ; i++ ) 
				{
					w[i][j]=w[i][j-4]^w[i][j-1]; 
				}
		}
	}
	return 0 ;
}

int numero_cle_aes(unsigned long int ** w , unsigned long int K[][4] , int numero ){

for (int i = 0; i <4 ; ++i)
	for (int j = 0; j <4 ; ++j )
	{
		K[i][j]=w[i][4*numero + j];
	}
	return 0 ;
}

void afficherTableau( unsigned long int  t[][4] , unsigned long int x, unsigned long int y)
{
    int i;
    int j;
    for(i=0; i<x; i++)
    {
        for(j=0; j<y; j++)
        {
            printf("%02lx \t ", t[i][j]);
 
        }
        printf("\n");
        printf("\n");
        printf("\n");
    }
}


int AddRoundKey(unsigned long int entre[][4] , unsigned long int cles[][4] )
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			entre[i][j]=entre[i][j]^cles[i][j];
		}
	}
	return 0;

}

int copie_tableau(unsigned long int entre[][4] , unsigned long int  sortie[][4] )
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			sortie[i][j]=entre[i][j];
		}
	}
	return 0 ;
}

/********************************************/
int XOR(unsigned long int tab1[][4] , unsigned long int tab2[][4] )
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			tab2[i][j]=tab2[i][j]^tab1[i][j];
		}
	}
	return 0;

}

int creer_fichier_128_bit(char *nom_fichier , unsigned long int tab[][4]){
	FILE *fic ;

	if ((fic= fopen(nom_fichier , "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier );
            return 0;
    }

    for (int i = 0; i < 4 ; ++i)
    {
    	for (int j = 0; j < 4 ; ++j)
    	{
    		fprintf(fic, "%02lx",tab[j][i] );
    	}
    }
    fclose(fic);
    return 1 ;

}

int lecture_cles_128_bit(char *nom_fichier , unsigned long int tab[][4]){
	FILE *fic ;
	int val ;
	int compteur=0 ;

	if ((fic= fopen(nom_fichier , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir  %s", nom_fichier );
            return 0;
    }
    fseek(fic , 0L , SEEK_END  );
    compteur=ftell(fic);
    fseek(fic,0L,SEEK_SET);
    
    fclose(fic);

    if (compteur!=32)
    {
    	fprintf(stderr, "\n erreur taille de cles incorrect dans le fichier :%s\n",nom_fichier );
    	fclose(fic);
    	return 0;
    }

    if ((fic= fopen(nom_fichier , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier );
            return 0;   }
    for (int i = 0; i < 4 ; ++i)
    {
    	for (int j = 0; j < 4 ; ++j)
    	{
    		fscanf(fic, "%02lx",&tab[j][i] );
    	}
    }
    fclose(fic);
	return 1;
}

int completer_fichier(char *nom_fichier  ){

    FILE *fic , *fic2;
    int i=0 ,val  , reste , mul_16 ;
    int car=0 ;

    if ((fic= fopen(nom_fichier , "rb+")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier );
            return 0;
    }

    while (( val = fgetc(fic)) !=EOF) {
       i++;
    }
    
    mul_16 = i/16;
    
    if ( i%16 == 0)
    {   
        fclose(fic);
        return mul_16 ;
        /* code */
    } 
    if ( i%16 != 0 )
        {   
            reste=i%16 ;
            reste = 16-reste ;

            for (int j = 0; j < reste; ++j)
            {   //putchar( (char)car );
                fputc( car , fic );
            }

            fclose(fic);
            mul_16 = mul_16 +1 ;
            return mul_16 ;
        }
}

int completer_fichier2(char *nom_fichier  ){

    FILE *fic , *fic2;
    int i=0 ,val  , reste , mul_16 ;
    int car=0 ;

    if ((fic= fopen(nom_fichier , "rb+")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier );
            return 0;
    }

    while (( val = fgetc(fic)) !=EOF) {
       i++;
    }
    
    mul_16 = i/16;
    
    if ( i%16 == 0)
    {   
        fclose(fic);
        return mul_16 ;
    }
    return 0;
    
}

int decouper_16(char *nom_fichier , int numero_curseur , unsigned long int tab[][4] ){
    FILE *fic ; 
    unsigned long int val ;
   
   if ((fic= fopen(nom_fichier, "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier );
            return 0;
    }
    fseek(fic , numero_curseur*16 , SEEK_SET );
    for (int i = 0; i < 4 ; ++i)
    {
        for (int j = 0; j < 4 ; ++j )
        {
            
        	//fread(&car, 1,1, fic);
        	
            val = fgetc( fic );
            tab[j][i]=val;
        }
    }
    fclose(fic);

    return 0 ;
}
/**********************************fin*******************/

/*******************fonction_inverse****************/
int Mixcolum_inverse(unsigned long int entre[][4] , unsigned long int sortie[][4] )
{
	int i,j,k;

	for ( i = 0; i < 4; ++i)
	{
		for ( j = 0; j < 4; ++j)
		{	
			sortie[j][i]=0x00;
			for ( k = 0; k < 4; ++k)
			{	
				if ( MatriceMixcolum_inverse[j][k]==0x0e )
				{
					sortie[j][i]=sortie[j][i]^mule[entre[k][i]] ;
				}
				
				if ( MatriceMixcolum_inverse[j][k]==0x0b )
				{
					sortie[j][i]=sortie[j][i] ^ mulb[entre[k][i]] ;
				}
				if ( MatriceMixcolum_inverse[j][k]==0x0d )
				{
					sortie[j][i]=sortie[j][i]^ muld[ entre[k][i] ] ;
				}
				if ( MatriceMixcolum_inverse[j][k]==0x09 )
				{
					sortie[j][i]=sortie[j][i]^ mul9[ entre[k][i] ] ;
				}
			}
		}
	}
	return 0 ;
}

int SubByte_inverse(unsigned long int entre[][4] )
{	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4 ; ++j)
		{
			entre[i][j] = invSBOX[entre[i][j]];
		}
	}

	return 0 ;
}

int ShiftRow_inverse(unsigned long int entre[][4] ){
	unsigned long int tempo , tempo2 ;
	int i ;
	for ( i = 1 ; i < 4; ++i)
	{
		if (i==1)
		{
			tempo=entre[1][3];
			entre[1][3]=entre[1][2];
			entre[1][2]=entre[1][1];
			entre[1][1]=entre[1][0] ;
			entre[1][0]=tempo;				
			}
		if (i==2)
		{
			tempo=entre[2][3];
			tempo2=entre[2][2];
			entre[2][2]=entre[2][0];
			entre[2][3]=entre[2][1];
			entre[2][1]=tempo;
			entre[2][0]=tempo2;
		}
		if (i==3)
		{
			tempo=entre[3][0];
			entre[3][0]=entre[3][1];
			entre[3][1]=entre[3][2];
			entre[3][2]=entre[3][3];
			entre[3][3]=tempo;
		}
	}

	return 0 ;
}


int Round_Aes_inverse(unsigned long int entre[][4] , unsigned long int cles[][4] )
{	unsigned long int sortie[4][4];
	
	ShiftRow_inverse(entre);
	SubByte_inverse(entre);
	AddRoundKey(entre , cles );
	Mixcolum_inverse(entre , sortie );
	/*copier la sortie dans le tableau entre*/
	copie_tableau(sortie , entre );
	return 0 ;
}

int AES_inverse(unsigned long int entre[][4] , unsigned long int cle_initiale[][4] ){
	unsigned long int **W ;
	unsigned long int cles[4][4];
	
	W=(unsigned long int **)malloc(4 * sizeof(unsigned long int *));
	for (int i = 0; i < 4; ++i) W[i]=(unsigned long int *)malloc(44*sizeof( unsigned long int )) ;
	/*etendre la cle initiale pour avoir les 11 sous cles dans W */
	
	expension_cle_rsa(cle_initiale , W );
	
	numero_cle_aes(W, cles , 10 );
	
	AddRoundKey(entre, cles );
	
	for (int i =9; i > 0 ; --i)
	{
		numero_cle_aes(W, cles , i );
		Round_Aes_inverse(entre , cles );
	}

	numero_cle_aes(W, cles , 0 );
	ShiftRow_inverse(entre);
	SubByte_inverse(entre);
	AddRoundKey(entre , cles );
}
/************************fin**************************/
/********************************gen.c*************/
 
int appele_srand = 0;
 
int generer_bornes(int min, int max)
{

    if(appele_srand != 1)
        initialiser_aleat((unsigned)time(NULL));
    return rand()%(max-min+1) + min;
}
 
void initialiser_aleat(unsigned int n)
{
    srand(n);
    appele_srand = 1;
}

void generer_key(unsigned long int K[][4]){

    unsigned long int val;
    initialiser_aleat((unsigned)time(NULL));
    for(int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j)
        {
            val=generer_bornes(0, 255);
             K[j][i]=val;
             //printf("%lx\n", val);
        }
              
    }

}

//le vecteur d initialisation pour le ECB--------------------
void vecteur_init(unsigned long int vect[][4]){

    unsigned long int val;
    initialiser_aleat((unsigned)time(NULL)+generer_bornes(23624,759494));
    for(int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j)
        {
            val=generer_bornes(0, 255);
             vect[j][i]=val;
             //printf("%lx\n", val);
        }
              
    }

}
/******************************fin**********************/
int Mixcolum(unsigned long int entre[][4] , unsigned long int sortie[][4] )
{
	int i,j,k;

	for ( i = 0; i < 4; ++i)
	{
		for ( j = 0; j < 4; ++j)
		{	
			sortie[j][i]=0x00;
			for ( k = 0; k < 4; ++k)
			{	
				if ( MatriceMixcolum[j][k]==0x01 )
				{
					sortie[j][i]=sortie[j][i]^entre[k][i] ;
				}
				
				if ( MatriceMixcolum[j][k]==0x02 )
				{
					sortie[j][i]=sortie[j][i] ^ mul2[entre[k][i]] ;
				}
				if ( MatriceMixcolum[j][k]==0x03 )
				{
					sortie[j][i]=sortie[j][i]^ mul3[ entre[k][i] ] ;
				}
			}
		}
	
	}
	return 0 ;// returne 0 si tout les calculs sont effectuee
}

int ShiftRow(unsigned long int entre[][4] ){
	unsigned long int tempo , tempo2 ;
	int i ;
	for ( i = 1 ; i < 4; ++i)
	{
		if (i==1)
		{
			tempo=entre[1][0];
			entre[1][0]=entre[1][1];
			entre[1][1]=entre[1][2];
			entre[1][2]=entre[1][3] ;
			entre[1][3]=tempo;				
			}
		if (i==2)
		{
			tempo=entre[2][0];
			tempo2=entre[2][1];
			entre[2][0]=entre[2][2];
			entre[2][1]=entre[2][3];
			entre[2][2]=tempo;
			entre[2][3]=tempo2;
		}
		if (i==3)
		{
			tempo=entre[3][3];
			entre[3][3]=entre[3][2];
			entre[3][2]=entre[3][1];
			entre[3][1]=entre[3][0];
			entre[3][0]=tempo;
		}
	}

	return 0 ;
}

int SubByte(unsigned long int entre[][4] )
{	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4 ; ++j)
		{
			entre[i][j] = SBOX_AES[entre[i][j]];
		}
	}

	return 0 ;
}

int Round_Aes(unsigned long int entre[][4] , unsigned long int cles[][4] )
{	unsigned long int sortie[4][4];
	SubByte(entre);
	ShiftRow(entre);
	Mixcolum(entre , sortie );
	AddRoundKey(sortie , cles );
	/*copier la sortie dans le tableau entre*/
	copie_tableau(sortie , entre );
	return 0 ;
}
/*la fonction de AES qui fait toute  les 10  tours*/
int AES(unsigned long int entre[][4] , unsigned long int cle_initiale[][4] ){
	unsigned long int **W ;
	unsigned long int cles[4][4];
	
	W=(unsigned long int **)malloc(4 * sizeof(unsigned long int *));
	for (int i = 0; i < 4; ++i) W[i]=(unsigned long int *)malloc(44*sizeof( unsigned long int )) ;
	/*etendre la cle initiale pour avoir les 11 sous cles dans W */
	expension_cle_rsa(cle_initiale , W );
	
	numero_cle_aes(W, cles , 0 );
	
	AddRoundKey(entre, cles );
	
	for (int i = 1; i < 10 ; ++i)
	{
		numero_cle_aes(W, cles , i );
		Round_Aes(entre , cles );
	}
	numero_cle_aes(W, cles , 10 );
	SubByte(entre);
	ShiftRow(entre);
	AddRoundKey(entre , cles );

}
/*******************************MODE ECB************************************************/


int ecb_aes_chiffrer(char *nom_fichier_entre , char *nom_fichier_sortie , char *fichier_key ){
    int mul_16 ; 
    FILE *fic , *fic1, *fic3 ;
    unsigned long int cle[4][4];
    unsigned long int donne[4][4];

    lecture_cles_128_bit(fichier_key , cle);

    if ((fic= fopen(nom_fichier_entre , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }
    if ((fic3= fopen("tmp/aes.tmp", "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }

    fseek(fic, 0L, SEEK_END);
    int  fileLen= ftell(fic);
    fseek(fic, 0L, SEEK_SET);
    char *buffer=calloc(fileLen+1,sizeof(char));
    fread(buffer, fileLen, 1, fic);
    fwrite(buffer,fileLen,1,fic3);
    fclose(fic);
    fclose(fic3);
    nom_fichier_entre = calloc(strlen("tmp/aes.tmp"), sizeof(char));
    strcpy(nom_fichier_entre,"tmp/aes.tmp");

    mul_16 = completer_fichier(nom_fichier_entre );

    if ((fic1= fopen(nom_fichier_sortie , "wb")) == NULL) 
    { 
      printf("Je ne peux pas ouvrir %s", nom_fichier_sortie );
      exit(1);
    }

    for (int k = 0 ; k < mul_16 ; ++k)
    {
        decouper_16(nom_fichier_entre , k , donne ) ;
        AES(donne , cle );
        //afficherTableau(donne,4,4);
        //printf("--------------------------\n");

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                //fprintf(fic1 , "%lx\t",donne[j][i] );
                fputc((int)donne[j][i] , fic1 );
            }
        }
    }
    fclose( fic1 );



return 1;
} 

int ecb_aes_dechiffrer(char *nom_fichier_entre , char *nom_fichier_sortie , char *fichier_key  ){
    int mul_16 ; 
    FILE *fic , *fic1, *fic3;
    unsigned long int donne[4][4] , cle[4][4];

    lecture_cles_128_bit( fichier_key, cle);

    if ((fic= fopen(nom_fichier_entre , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }
    if ((fic3= fopen("tmp/aes.tmp", "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }

    fseek(fic, 0L, SEEK_END);
    int  fileLen= ftell(fic);
    fseek(fic, 0L, SEEK_SET);
    char *buffer=calloc(fileLen+1,sizeof(char));
    fread(buffer, fileLen, 1, fic);
    fwrite(buffer,fileLen,1,fic3);
    fclose(fic);
    fclose(fic3);
    nom_fichier_entre = calloc(strlen("tmp/aes.tmp"), sizeof(char));
    strcpy(nom_fichier_entre,"tmp/aes.tmp");

   /****************************************************/
   /*               A CORRIGER                         */
    mul_16 = completer_fichier2(nom_fichier_entre );
    if(mul_16==0)
        return 0;

    if ((fic1= fopen(nom_fichier_sortie , "wb")) == NULL) {
        printf("Je ne peux pas ouvrir %s", nom_fichier_sortie );
        return 0 ;
    }

    for (int k = 0 ; k < mul_16 ; ++k)
    {
        decouper_16(nom_fichier_entre , k , donne ) ;
        AES_inverse(donne , cle );
        //afficherTableau(donne,4,4);
        //printf("--------------------------\n");

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                //fprintf(fic1 , "%lx\t",donne[j][i] );
                fputc((int)donne[j][i] , fic1 );
            }
        }
    }
    
    fclose( fic1 );
    paddingExtractor(nom_fichier_sortie);

return 1;
} 


int CBC_aes_chiffrer(char *nom_fichier_entre , char *nom_fichier_sortie , char *fichier_key , char *fichier_vecteur_initial ){
    int mul_16 ; 

    FILE *fic , *fic1, *fic3 ;
    unsigned long int donne[4][4]  , donne1[4][4] ;
    unsigned long int vecteur[4][4] , cle[4][4] ;

    lecture_cles_128_bit( fichier_key, cle);
    //vecteur_init(vecteur);
    if ((fic= fopen(nom_fichier_entre , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }
    if ((fic3= fopen("tmp/aes.tmp", "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }

    fseek(fic, 0L, SEEK_END);
    int  fileLen= ftell(fic);
    fseek(fic, 0L, SEEK_SET);
    char *buffer=calloc(fileLen+1,sizeof(char));
    fread(buffer, fileLen, 1, fic);
    fwrite(buffer,fileLen,1,fic3);
    fclose(fic);
    fclose(fic3);
    nom_fichier_entre = calloc(strlen("tmp/aes.tmp"), sizeof(char));
    strcpy(nom_fichier_entre, "tmp/aes.tmp");

    

    lecture_cles_128_bit( fichier_vecteur_initial , vecteur );

    mul_16 = completer_fichier(nom_fichier_entre );

    if ((fic1= fopen(nom_fichier_sortie , "wb")) == NULL) {
        printf("Je ne peux pas ouvrir %s", nom_fichier_sortie );
        return 0;
    }
   
    decouper_16(nom_fichier_entre , 0 , donne ) ;
    XOR(vecteur , donne);
    AES(donne , cle );
    /**ecrire dans le fichier**/
    for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                //fprintf(fic1 , "%lx\t",donne[j][i] );
                fputc((int)donne[j][i] , fic1 );
            }
        }
    /*****fin ecritutre***/
    for (int k = 1 ; k < mul_16 ; ++k)
    {
        decouper_16(nom_fichier_entre , k , donne1 ) ;
        XOR(donne1 , donne );
        AES(donne , cle );
        //afficherTableau(donne,4,4);
        //printf("--------------------------\n");

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                //fprintf(fic1 , "%lx\t",donne[j][i] );
                fputc((int)donne[j][i] , fic1 );
            }
        }
    }
    
    fclose( fic1 );



return 1;
} 

int CBC_aes_dechiffrer(char *nom_fichier_entre , char *nom_fichier_sortie , char *fichier_key , char *fichier_vecteur_initial ){
    int mul_16 ; 
    FILE *fic , *fic1, *fic3 ;
    unsigned long int donne[4][4]  , donne1[4][4] , tampo[4][4] ;
    unsigned long int vecteur[4][4] , cle[4][4];

    //vecteur_init(vecteur);
    lecture_cles_128_bit( fichier_vecteur_initial , vecteur);
    lecture_cles_128_bit( fichier_key, cle);
     if ((fic= fopen(nom_fichier_entre , "rb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }
    if ((fic3= fopen("tmp/aes.tmp", "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_entre );
            return 0;
    }

    fseek(fic, 0L, SEEK_END);
    int  fileLen= ftell(fic);
    fseek(fic, 0L, SEEK_SET);
    char *buffer=calloc(fileLen+1,sizeof(char));
    fread(buffer, fileLen, 1, fic);
    fwrite(buffer,fileLen,1,fic3);
    fclose(fic);
    fclose(fic3);
    strcpy(nom_fichier_entre,"tmp/aes.tmp");

    mul_16 = completer_fichier2(nom_fichier_entre );

    if(mul_16 ==0)
        return 0;

    if ((fic1= fopen(nom_fichier_sortie , "wb")) == NULL) {
            printf("Je ne peux pas ouvrir %s", nom_fichier_sortie );
            return 0 ;
    }
   

    for (int k = 0 ; k < mul_16 ; ++k)
    {
        decouper_16(nom_fichier_entre , k , donne ) ;
        copie_tableau(donne ,tampo );
        AES_inverse(donne , cle );
        XOR(vecteur , donne );
        copie_tableau(tampo,vecteur);
        //afficherTableau(donne,4,4);
        //printf("--------------------------\n");

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                //fprintf(fic1 , "%lx\t",donne[j][i] );
                fputc((int)donne[j][i] , fic1 );
            }
        }
    }
    fclose( fic1 );
    paddingExtractor(nom_fichier_sortie);


return 1;
} 


/********************************************************************/
char * CBC_MAC_AES(char *nom_fichier_entre , char *nom_fichier_sortie , char *fichier_key, char *sortie ){
  FILE *fic;
  if ((fic= fopen("tmp/tmp.iv.key" , "wb")) == NULL) {
            printf("Je ne peux pas ouvrir ");
            return 0;
   }
    /*********************************************************/
    /*          MAC CBC IV = 0                               *
    **********************************************************/
    char *buf1 = calloc(33,sizeof(char));
    for (int i = 0, j = 0; i < 16; ++i, j += 2)
                sprintf(buf1 + j, "%02x", 0 & 0xff);
    fwrite(buf1,32,1,fic);
    fclose(fic);

    int ret = CBC_aes_chiffrer(nom_fichier_entre ,nom_fichier_sortie ,fichier_key, "tmp/tmp.iv.key");
    if (ret == 1){
        fic= fopen(nom_fichier_sortie , "rb");
        char buf2[16];
        fseek(fic, -16, SEEK_END);
        fread(buf2, 16, 1, fic);
        fclose(fic);
        for (int i = 0, j = 0; i < 16; ++i, j += 2)
                sprintf(buf1 + j, "%02x", buf2[i] & 0xff);
        buf1[32]='\0';
        fic= fopen(nom_fichier_sortie , "wb");
        fwrite(buf1,32,1,fic);
        fclose(fic);
        strcpy(sortie,buf1);
        return sortie;
    }

    return "";
} 

