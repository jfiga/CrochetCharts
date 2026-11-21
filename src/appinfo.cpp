/****************************************************************************\
 Copyright (c) 2010-2014 Stitch Works Software
 Brian C. Milco <bcmilco@gmail.com>

 This file is part of Crochet Charts.

 Crochet Charts is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Crochet Charts is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Crochet Charts. If not, see <http://www.gnu.org/licenses/>.

 \****************************************************************************/
#include "appinfo.h"

AppInfo* AppInfo::mInstance = NULL;

AppInfo::AppInfo() :
    appName("Crochet Charts"),
    appOrg("Stitch Works Software"),
    
    appOrgDomain("StitchWorksSoftware.com"), 
    appOrgContact("http://StitchWorksSoftware.com/contact"),

    appVersion(gGIT_VERSION),
    appVersionShort(gGIT_VERSION_SHORT),
    appBuildInfo(QString(__DATE__) + " " + QString(__TIME__)),


    demoString(QObject::tr("Stitch Works Software - Demo Version  -  ")),

    projectLife(gPROJECT_LIFE),

    magicNumber(0x95973530),
    magicNumberSet(0x53095973)
{
}
