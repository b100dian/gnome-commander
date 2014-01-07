/*
  GNOME Commander - A GNOME based file manager
  Copyright (C) 2001-2006 Marcus Bjurman
  Copyright (C) 2007-2012 Piotr Eljasiak
    Copyright (C) 2013-2014 Uwe Scholz

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

   Author: Assaf Gordon  <agordon88@gmail.com>
*/

#include <glib.h>
#include <stdio.h>
#include <libgviewer/gvtypes.h>
#include <libgviewer/bm_byte.h>

int main()
{
    const guint8 pattern[] = { 0x01, 0x04, 0xB4, 0xFE, 0x01, 0x01, 0x04};
    const guint8 text[] = {
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,
0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,
0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,
0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,
0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x01,0x04,0x59,0x5a,
0x5b,0x5c,0x5d,0x5e,0x5f,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,
0x6a,0x6b,0x6c,0x6d,0x01,0x01,0x04,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,
0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,
0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x01,0x04,0xB4,0xFE,0x01,0x01,0x04,0x96, //match on this line
0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,
0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xc2,0xc3,
0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0x05,0x04,
0xB4,0xFe,0x01,0x01,0x04,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,0xe0,0xe1,
0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,0xf0,
0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0x01,0x04,0xb4,0xfe,0x01,0x01,0x04,0x00}; // match on this line, too
    int i;
    int j;
    int m;
    int n;

    GViewerBMByteData *data;

    data = create_bm_byte_data(pattern,sizeof(pattern));

    printf("Good suffices table:\n");
    for (i=0;i<data->pattern_len;i++)
        printf("%d ", data->good[i]);
    printf("\n\n");

    printf("Bad characters table:\nChar(ASCII)\tValue\n");
    for (i=0;i<256;i++) {
        if (data->bad[i] != data->pattern_len) {
            printf("%c(%d)\t\t%d\n",i,i, data->bad[i]);
        }
    }
    printf("(All other characters have value of %d)\n\n", data->pattern_len);

    // Do the actual search
    m = data->pattern_len;
    n = sizeof(text);
    j = 0;
    while (j <= n - m) {
        for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; --i);
        if (i < 0) {
            printf(" Found match at offset = %d\n", j);
            j += data->good[0];
        }
        else
            j += MAX(data->good[i], data->bad[(int)text[i + j]] - m + 1 + i);
    }

    free_bm_byte_data(data);

    return 0;
}
