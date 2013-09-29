class stringUtils {
	
public:
	
	typedef struct{
		string character;
		string code;
	}charSubstitution; 
	
	static string subsChars(string origString){
		charSubstitution chars[]={
			{"À","\xC0"}, {"Á","\xC1"}, {"Â","\xC2"}, {"Ã","\xC3"}, {"Ã","\xC4"}, {"Å","\xC5"}, {"Æ","\xC6"},
			{"à","\xE0"}, {"á","\xE1"}, {"â","\xE2"}, {"ã","\xE3"}, {"ä","\xE4"}, {"å","\xE5"}, {"æ","\xE6"},
			{"Ç","\xC7"},
			{"ç","\xE7"},
			{"È","\xC8"}, {"É","\xC9"}, {"Ê","\xCA"}, {"Ë","\xCB"},
			{"è","\xE8"}, {"é","\xE9"}, {"ê","\xEA"}, {"ë","\xEB"},
			{"Ì","\xCC"}, {"Í","\xCD"}, {"Î","\xCE"}, {"Ï","\xCF"},
			{"ì","\xEC"}, {"í","\xED"}, {"î","\xEE"}, {"ï","\xEF"},
			{"Ñ","\xD1"},
			{"ñ","\xF1"},
			{"Ò","\xD2"}, {"Ó","\xD3"}, {"Ô","\xD4"}, {"Õ","\xD5"}, {"Ö","\xD6"}, {"Ø","\xD8"},
			{"ò","\xF2"}, {"ó","\xF3"}, {"ô","\xF4"}, {"õ","\xF5"}, {"ö","\xF6"}, {"ø","\xF8"},
			{"ß","\xDF"},
			{"Ù","\xD9"}, {"Ú","\xDA"}, {"Û","\xDB"}, {"Ü","\xDC"},
			{"ù","\xF9"}, {"ú","\xFA"}, {"û","\xFB"}, {"ü","\xFC"},
			{"ÿ","\xFF"}, {"ý","\xFD"}, 
			{"-","\xAD"}, {"\"","\x22"}, {"'","\x27"}, {"-","\x2D"}, {"<","\x3C"}, {"=","\x3D"}, {">","\x3E"},
			{"¡","\xA1"}, {"¢","\xA2"}, {"£","\xA3"}, {"¤","\xA4"}, {"¥","\xA5"}, {"¦","\xA6"}, {"§","\xA7"},
			{"¨","\xA8"}, {"©","\xA9"}, {"ª","\xAA"}, {"«","\xAB"}, {"¬","\xAC"}, {"®","\xAE"}, {"¯","\xAF"},
			{"°","\xB0"}, {"±","\xB1"}, {"²","\xB2"}, {"³","\xB3"}, {"´","\xB4"}, {"µ","\xB5"}, {"¶","\xB6"},
			{"·","\xB7"}, {"¸","\xB8"}, {"¹","\xB9"}, {"º","\xBA"}, {"»","\xBB"}, {"¼","\xBC"}, {"½","\xBD"},
			{"¾","\xBE"}, {"¿","\xBF"}, {"Ð","\xD0"}, {"Ý","\xDD"}, {"Þ","\xDE"}, {"ð","\xF0"}, {"÷","\xF7"},
			{"þ","\xFE"}
		};
		
		for(int i=0; i<100; i++){
			
			while(origString.find(chars[i].character)!=string::npos){
				origString = origString.substr(0,origString.find(chars[i].character)) + chars[i].code + origString.substr(origString.find(chars[i].character)+2);
			}
		};
		
		return origString;
	}
	
};
