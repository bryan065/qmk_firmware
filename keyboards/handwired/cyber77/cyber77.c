/*
  Copyright (c) 2022 Bryan065

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

//========Keyboard & RGB matrix strip wiring / index====//
/*
*   ___________________________________
*  /   0          1  2  3  4  5  6     \_____________          <-- Light bar
* ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
* │ 7 │ 8 │ 9 │ 10│ 11│ 12│ 13│ 14│ 15│ 16│ 17│ 18│ 19│ 20    │21 │
* ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
* │ 36  │35 │34 │33 │32 │31 │30 │29 │28 │27 │26 │25 │24 │23   │22 │
* ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
* │ 37   │38 │39 │40 │41 │42 │43 │44 │45 │46 │47 │48 │  49    │50 │
* ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
* │ 64     │63 │62 │61 │60 │59 │58 │57 │56 │55 │54 │53    │51 │51 │
* ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
* │ 65 │ 66 │ 67 │  68      │ 69 │  70    │71 │72 │   │73 │74 │75 │
* └────┴────┴────┴──────────┴────┴────────┴───┴───┘   └───┴───┴───┘
*/


#ifdef RGB_MATRIX_ENABLE
//LED TO MATRIX MAP
led_config_t g_led_config = { {
        // Key Matrix to LED Index
        {      7,      8,      9,     10,     11,     12,     13,     14,     15, 16, 17, 18,     19,     20,     21 },
        {     36,     35,     34,     33,     32,     31,     30,     29,     28, 27, 26, 25,     24,     23,     22 },
        {     37,     38,     39,     40,     41,     42,     43,     44,     45, 46, 47, 48, NO_LED,     49,     50 },
        {     64,     63,     62,     61,     60,     59,     58,     57,     56, 55, 54, 53, NO_LED,     52,     51 },
        {     65,     66,     67,     68, NO_LED,     69, NO_LED,     70, NO_LED, 71, 72, 73, NO_LED,     74,     75 }
    }, {
        // LED Index to Physical Position **BASED ON KEY MATRIX TO LED INDEX (back and fourth snake in this case)
        {10,0},{50,0},{62,0},{74,0},{86,0},{98,0},{110,0},
        {0,12},{15,12},{30,12},{45,12},{60,12},{75,12},{90,12},{105,12},{120,12},{135,12},{150,12},{165,12},{180,12},{203,12},{224,12},
        {224,25},{203,25},{180,25},{165,25},{150,25},{135,25},{120,25},{105,25},{90,25},{75,25},{60,25},{45,25},{30,25},{15,25},{0,25},
        {0,38},{25,38},{40,38},{55,38},{70,38},{85,38},{100,38},{115,38},{130,38},{145,38},{160,38},{175,38},{201,38},{224,38},
        {224,51},{210,51},{189,51},{169,51},{154,51},{139,51},{120,51},{105,51},{90,51},{75,51},{60,51},{45,51},{25,51},{5,51},
        {2,64},{21,64},{39,64},{70,64},{90,64},{120,64},{150,64},{165,64},{190,64},{205,64},{224,64}
    }, {
        // LED Index to Flag
        2,2,2,2,2,2,2, // Lightbar
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1, 1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1,
        1, 1, 1,    1,    1,    1,    1, 1, 4, 4, 4,
    }
};
#endif
