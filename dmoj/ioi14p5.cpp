#include <bits/stdc++.h>
#define _______ 0
#define ________ 1
#define _________ int
#define __________ for
#define ___________ if
#define ____________ else
#define _____________ max
#define ______________ return
using namespace std;

_________ findSample(_________ ______, _________ *__, _________ *___, _________ *____){
	_________ _____ = _______;
	__________(_________ _=______-________;_>_______;_--){
		___________(____[_]==_______){
			_____ += __[_];
			__[___[_]] = _____________(__[___[_]]-__[_],_______);
		}
		____________ ___________(____[_]==________)
			__[___[_]] += __[_];
		____________
			__[___[_]] = _____________(__[___[_]],__[_]);
	}
	______________ _____+__[_______];
}
