/*
 *  Copyright 2020 catsout  <outl941@163.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  2.010-1301, USA.
 */

.pragma library

// Use try Qt.createQmlObject to check if c++ lib is installed
// Use try, as Qt.createQmlObject may break the function
// TODO: add CheckItem for c++ lib object, like mpvChecker{} intead of QtObject{}
function checklib(parentItem) {
	var ok = false;
	var create = null;
	 try {
		create = Qt.createQmlObject(
		'import com.github.catsout.wallpaperEngineKde 1.0;import QtQml 2.13;QtObject{}',
		parentItem);

	} catch (error) {}
	if(create != null){
		ok = true;
		create.destroy(1000);
	}
	return ok;
}
