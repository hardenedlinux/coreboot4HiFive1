##
## This file is part of the coreboot project.
##
## Copyright (C) 2013 Google Inc.
##
## This software is licensed under the terms of the GNU General Public
## License version 2, as published by the Free Software Foundation, and
## may be copied, distributed, and modified under those terms.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.


bootblock-y += memlayout.ld
romstage-y  += memlayout.ld
ramstage-y  += memlayout.ld

ramstage-y  += mainboard.c

CPPFLAGS_common += -Isrc/mainboard/sifive/freedom-e300-hifive1/include
