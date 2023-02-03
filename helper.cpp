/*
 MIT License
 
 Copyright (c) 2019 Fredrik B
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "poddl.hpp"

/*
	/ \ * ? | <> : "
*/
const std::map<std::string, std::string> bad_filename_characters
{
	{"<", ""},
	{">", ""},
	{"|", ""},
	{"?", ""},
	{"*", ""},
    {":", ""},
    {"/", ""},
    {"\\", ""},
	{"\"", ""}
};

const std::map<std::string, std::string> html_entities
{
	{"&quot;", "\""},
	{"&amp;", "&"},
    {"&#32;", " "},
    {"&#33;", "!"},
    {"&#34;", ""},
    {"&#35;", "#"},
    {"&#36;", "$"},
    {"&#37;", "%"},
    {"&#38;", "&"},
    {"&#39;", "'"},
    {"&#40;", "("},
    {"&#41;", ")"},
    {"&#42;", "*"},
    {"&#43;", "+"},
    {"&#44;", ","},
    {"&#45;", "-"},
    {"&#46;", "."},
    {"&#47;", "/"},
    {"&#48;", "0"},
    {"&#49;", "1"},
    {"&#50;", "2"},
    {"&#51;", "3"},
    {"&#52;", "4"},
    {"&#53;", "5"},
    {"&#54;", "6"},
    {"&#55;", "7"},
    {"&#56;", "8"},
    {"&#57;", "9"},
    {"&#58;", ":"},
    {"&#59;", ";"},
    {"&#60;", "<"},
    {"&#61;", "="},
    {"&#62;", ">"},
    {"&#63;", "?"},
    {"&#64;", "@"},
    {"&#65;", "A"},
    {"&#66;", "B"},
    {"&#67;", "C"},
    {"&#68;", "D"},
    {"&#69;", "E"},
    {"&#70;", "F"},
    {"&#71;", "G"},
    {"&#72;", "H"},
    {"&#73;", "I"},
    {"&#74;", "J"},
    {"&#75;", "K"},
    {"&#76;", "L"},
    {"&#77;", "M"},
    {"&#78;", "N"},
    {"&#79;", "O"},
    {"&#80;", "P"},
    {"&#81;", "Q"},
    {"&#82;", "R"},
    {"&#83;", "S"},
    {"&#84;", "T"},
    {"&#85;", "U"},
    {"&#86;", "V"},
    {"&#87;", "W"},
    {"&#88;", "X"},
    {"&#89;", "Y"},
    {"&#90;", "Z"},
    {"&#91;", "["},
    {"&#92;", "\\"},
    {"&#93;", "]"},
    {"&#94;", "^"},
    {"&#95;", "_"},
    {"&#96;", "`"},
    {"&#97;", "a"},
    {"&#98;", "b"},
    {"&#99;", "c"},
    {"&#100;", "d"},
    {"&#101;", "e"},
    {"&#102;", "f"},
    {"&#103;", "g"},
    {"&#104;", "h"},
    {"&#105;", "i"},
    {"&#106;", "j"},
    {"&#107;", "k"},
    {"&#108;", "l"},
    {"&#109;", "m"},
    {"&#110;", "n"},
    {"&#111;", "o"},
    {"&#112;", "p"},
    {"&#113;", "q"},
    {"&#114;", "r"},
    {"&#115;", "s"},
    {"&#116;", "t"},
    {"&#117;", "u"},
    {"&#118;", "v"},
    {"&#119;", "w"},
    {"&#120;", "x"},
    {"&#121;", "y"},
    {"&#122;", "z"},
    {"&#123;", "{"},
    {"&#124;", "|"},
    {"&#125;", "}"},
    {"&#126;", "~"},
    
    {"&#192;", "À"},
    {"&#193;", "Á"},
    {"&#194;", "Â"},
    {"&#195;", "Ã"},
    {"&#196;", "Ä"},
    {"&#197;", "Å"},
    {"&#198;", "Æ"},
    {"&#199;", "Ç"},
    {"&#200;", "È"},
    {"&#201;", "É"},
    {"&#202;", "Ê"},
    {"&#203;", "Ë"},
    {"&#204;", "Ì"},
    {"&#205;", "Í"},
    {"&#206;", "Î"},
    {"&#207;", "Ï"},
    {"&#208;", "Ð"},
    {"&#209;", "Ñ"},
    {"&#210;", "Ò"},
    {"&#211;", "Ó"},
    {"&#212;", "Ô"},
    {"&#213;", "Õ"},
    {"&#214;", "Ö"},
    {"&#216;", "Ø"},
    {"&#217;", "Ù"},
    {"&#218;", "Ú"},
    {"&#219;", "Û"},
    {"&#220;", "Ü"},
    {"&#221;", "Ý"},
    {"&#222;", "Þ"},
    {"&#223;", "ß"},
    {"&#224;", "à"},
    {"&#225;", "á"},
    {"&#226;", "â"},
    {"&#227;", "ã"},
    {"&#228;", "ä"},
    {"&#229;", "å"},
    {"&#230;", "æ"},
    {"&#231;", "ç"},
    {"&#232;", "è"},
    {"&#233;", "é"},
    {"&#234;", "ê"},
    {"&#235;", "ë"},
    {"&#236;", "ì"},
    {"&#237;", "í"},
    {"&#238;", "î"},
    {"&#239;", "ï"},
    {"&#240;", "ð"},
    {"&#241;", "ñ"},
    {"&#242;", "ò"},
    {"&#243;", "ó"},
    {"&#244;", "ô"},
    {"&#245;", "õ"},
    {"&#246;", "ö"},
    {"&#248;", "ø"},
    {"&#249;", "ù"},
    {"&#250;", "ú"},
    {"&#251;", "û"},
    {"&#252;", "ü"},
    {"&#253;", "ý"},
    {"&#254;", "þ"},
    {"&#255;", "ÿ"},
    
    {"&#160;", " "},
    {"&#161;", "¡"},
    {"&#162;", "¢"},
    {"&#163;", "£"},
    {"&#164;", "¤"},
    {"&#165;", "¥"},
    {"&#166;", "¦"},
    {"&#167;", "§"},
    {"&#168;", "¨"},
    {"&#169;", "©"},
    {"&#170;", "ª"},
    {"&#171;", "«"},
    {"&#172;", "¬"},
    {"&#173;", "-"},
    {"&#174;", "®"},
    {"&#175;", "¯"},
    {"&#176;", "°"},
    {"&#177;", "±"},
    {"&#178;", "²"},
    {"&#179;", "³"},
    {"&#180;", "´"},
    {"&#181;", "µ"},
    {"&#182;", "¶"},
    {"&#184;", "¸"},
    {"&#185;", "¹"},
    {"&#186;", "º"},
    {"&#187;", "»"},
    {"&#188;", "¼"},
    {"&#189;", "½"},
    {"&#190;", "¾"},
    {"&#191;", "¿"},
    {"&#215;", "×"},
    {"&#247;", "÷"},
    
    {"&#8704;", "∀"},
    {"&#8706;", "∂"},
    {"&#8707;", "∃"},
    {"&#8709;", "∅"},
    {"&#8711;", "∇"},
    {"&#8712;", "∈"},
    {"&#8713;", "∉"},
    {"&#8715;", "∋"},
    {"&#8719;", "∏"},
    {"&#8721;", "∑"},
    {"&#8722;", "−"},
    {"&#8727;", "∗"},
    {"&#8730;", "√"},
    {"&#8733;", "∝"},
    {"&#8734;", "∞"},
    {"&#8736;", "∠"},
    {"&#8743;", "∧"},
    {"&#8744;", "∨"},
    {"&#8745;", "∩"},
    {"&#8746;", "∪"},
    {"&#8747;", "∫"},
    {"&#8756;", "∴"},
    {"&#8764;", "∼"},
    {"&#8773;", "≅"},
    {"&#8776;", "≈"},
    {"&#8800;", "≠"},
    {"&#8801;", "≡"},
    {"&#8804;", "≤"},
    {"&#8805;", "≥"},
    {"&#8834;", "⊂"},
    {"&#8835;", "⊃"},
    {"&#8836;", "⊄"},
    {"&#8838;", "⊆"},
    {"&#8839;", "⊇"},
    {"&#8853;", "⊕"},
    {"&#8855;", "⊗"},
    {"&#8869;", "⊥"},
    {"&#8901;", "⋅"},
    
    {"&#913;", "Α"},
    {"&#914;", "Β"},
    {"&#915;", "Γ"},
    {"&#916;", "Δ"},
    {"&#917;", "Ε"},
    {"&#918;", "Ζ"},
    {"&#919;", "Η"},
    {"&#920;", "Θ"},
    {"&#921;", "Ι"},
    {"&#922;", "Κ"},
    {"&#923;", "Λ"},
    {"&#924;", "Μ"},
    {"&#925;", "Ν"},
    {"&#926;", "Ξ"},
    {"&#927;", "Ο"},
    {"&#928;", "Π"},
    {"&#929;", "Ρ"},
    {"&#931;", "Σ"},
    {"&#932;", "Τ"},
    {"&#933;", "Υ"},
    {"&#934;", "Φ"},
    {"&#935;", "Χ"},
    {"&#936;", "Ψ"},
    {"&#937;", "Ω"},
    {"&#945;", "α"},
    {"&#946;", "β"},
    {"&#947;", "γ"},
    {"&#948;", "δ"},
    {"&#949;", "ε"},
    {"&#950;", "ζ"},
    {"&#951;", "η"},
    {"&#952;", "θ"},
    {"&#953;", "ι"},
    {"&#954;", "κ"},
    {"&#955;", "λ"},
    {"&#956;", "μ"},
    {"&#957;", "ν"},
    {"&#958;", "ξ"},
    {"&#959;", "ο"},
    {"&#960;", "π"},
    {"&#961;", "ρ"},
    {"&#962;", "ς"},
    {"&#963;", "σ"},
    {"&#964;", "τ"},
    {"&#965;", "υ"},
    {"&#966;", "φ"},
    {"&#967;", "χ"},
    {"&#968;", "ψ"},
    {"&#969;", "ω"},
    {"&#977;", "ϑ"},
    {"&#978;", "ϒ"},
    {"&#982;", "ϖ"},
    
    {"&#338;", "Œ"},
    {"&#339;", "œ"},
    {"&#352;", "Š"},
    {"&#353;", "š"},
    {"&#376;", "Ÿ"},
    {"&#402;", "ƒ"},
    {"&#710;", "ˆ"},
    {"&#732;", "˜"},
    {"&#8194;", " "},
    {"&#8195;", " "},
    {"&#8201;", " "},
    {"&#8204;", " "},
    {"&#8205;", " "},
    {"&#8206;", ""},
    {"&#8211;", "–"},
    {"&#8212;", "—"},
        
    {"&#8216;", "‘"},
    {"&#8217;", "’"},
    {"&#8218;", "‚"},
    {"&#8220;", "“"},
    {"&#8221;", "”"},
    {"&#8222;", "„"},
    {"&#8224;", "†"},
    {"&#8225;", "‡"},
    {"&#8226;", "•"},
    {"&#8230;", "…"},
    {"&#8240;", "‰"},
    {"&#8242;", "′"},
    {"&#8243;", "″"},
    {"&#8249;", "‹"},
    {"&#8250;", "›"},
    {"&#8254;", "‾"},
    {"&#8364;", "€"},
    {"&#8482;", "™"},
    {"&#8592;", "←"},
    {"&#8593;", "↑"},
    {"&#8594;", "→"},
    {"&#8595;", "↓"},
    {"&#8596;", "↔"},
    {"&#8629;", "↵"},
    {"&#8968;", "⌈"},
    {"&#8969;", "⌉"},
    {"&#8970;", "⌊"},
    {"&#8971;", "⌋"},
    {"&#9674;", "◊"},
    {"&#9824;", "♠"},
    {"&#9827;", "♣"},
    {"&#9829;", "♥"},
    {"&#9830;", "♦"}
};

const std::string media_extensions[] =
{ 
    "mp3","m4a","mp4","ogg","oga","aac","flac","wma","wmv","mpg","mpeg","avi","m4v","mov","ac3","pcm","wav","alac","webm" 
};

#ifdef _WIN32
std::vector<std::string> Helper::get_args(int argc, const wchar_t *argv[]) {
	std::vector<std::string> v;
	
	for (int i = 1; i < argc; i++) {
		const wchar_t *arg = argv[i];
		const std::wstring wstr(arg);
		const std::string str = Helper::wide_win_string_to_utf8(wstr);
		v.push_back(str);
	}

	return v;
}
#else
std::vector<std::string> Helper::get_args(int argc, const char *argv[]) {
	std::vector<std::string> v;
	
	for (int i = 1; i < argc; i++) {
		const char *arg = argv[i];
		const std::string str(arg);
		v.push_back(str);
	}

	return v;
}
#endif

int int_try_parse(std::string text) {
	char* endptr;
	int number = strtol(text.c_str(), &endptr, 10);

	if (endptr == text.c_str() + text.size()) {
		return number;
	}

	return 0;
}

Options Helper::get_options(std::vector<std::string> args) {
	Options options;

	for (size_t i = 0; i != args.size(); i++) {
		auto const x = args[i];

		if (x == "-n") {
			if ( !(i + 1 <= args.size() - 1) ) {
				continue;
			}

			auto const n = args[i + 1];
			auto const d = n.find("-");

			if (d != std::string::npos) {
				auto const a = n.substr(0, d);
				auto const b = n.substr(d + 1);

				options.episode_from = int_try_parse(a);
				options.episode_to = int_try_parse(b);
			} else {
				options.episode_from = int_try_parse(n);
				options.episode_to = options.episode_from;
			}

			i = i + 1;
		} else if (x == "-l") {
			options.list_only = true;
		} else {
			/* this will hopefully prevent a breaking change */
			if (options.url.empty()) {
				options.url = url_encode_lazy(html_decode(x));
			} else {
				options.path = x;
			}
		}
	}

	return options;
}

void replace_substring(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

std::string Helper::html_decode(std::string input) {
    for (auto const &x : html_entities) {
        std::size_t found = input.find(x.first);
        if (found != std::string::npos) {
            replace_substring(input, x.first, x.second);
        }
    }
    
    return input;
}

std::string Helper::clean_filename(std::string input) {
    for (auto const &x : bad_filename_characters) {
        std::size_t found = input.find(x.first);
        if (found != std::string::npos) {
            replace_substring(input, x.first, x.second);
        }
    }
    
    return input;
}

std::string Helper::url_encode_lazy(std::string input) {
    replace_substring(input, " ", "%20");
    return input;
}

std::string Helper::get_extension(std::string input) {
    for (auto const &x : media_extensions) {
        const std::string needle = "." + x;
        bool found = input.find(needle) != std::string::npos;
        if (found) {
            return x;
        }
    }

    //fallback
    return "mp3";
}

#ifdef _WIN32
std::wstring Helper::utf8_to_wide_win_string(std::string input) {
    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL ,0);
    if (wchars_num <= 0) {
        return std::wstring();
    }

    wchar_t* wstr = new wchar_t[wchars_num];
    wchars_num = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, wstr, wchars_num);

    std::wstring output(wstr);
    delete[] wstr;

    return output;
}

std::string Helper::wide_win_string_to_utf8(std::wstring input) {
    int chars_num = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, NULL);
    if (chars_num <= 0) {
        return std::string();
    }

    char* str = new char[chars_num];
    chars_num = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, str, chars_num, NULL, NULL);
    
    std::string output(str);
    delete[] str;
    
    return output;
}
#endif