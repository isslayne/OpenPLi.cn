/*
	Neutrino-GUI  -   DBoxII-Project
 
	Copyright (C) 2001 Steffen Hehn 'McClean'
	Homepage: http://dbox.cyberphoria.org/
 
	Kommentar:
 
	Diese GUI wurde von Grund auf neu programmiert und sollte nun vom
	Aufbau und auch den Ausbaumoeglichkeiten gut aussehen. Neutrino basiert
	auf der Client-Server Idee, diese GUI ist also von der direkten DBox-
	Steuerung getrennt. Diese wird dann von Daemons uebernommen.
	
 
	License: GPL
 
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
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


struct ISO639
{
	char *iso639foreign, *iso639int, *twoletterm, *description1, *description2;
}
iso639[]=
    {
        {"aar", "aar", "aa", "Afar", "Hamitic"},
        {"abk", "abk", "ab", "Abkhazian", "Ibero-caucasian"},
        {"ace", "ace", "", "Achinese", ""},
        {"ach", "ach", "", "Acoli", ""},
        {"ada", "ada", "", "Adangme", ""},
        {"afa", "afa", "", "Afro-Asiatic (Other)", ""},
        {"afh", "afh", "", "Afrihili", ""},
        {"afr", "afr", "af", "Afrikaans", "Germanic"},
        {"aka", "aka", "", "Akan", ""},
        {"akk", "akk", "", "Akkadian", ""},
        {"ale", "ale", "", "Aleut", ""},
        {"alg", "alg", "", "Algonquian languages", ""},
        {"amh", "amh", "am", "Amharic", "Semitic"},
        {"ang", "ang", "", "English, Old (ca. 450-1100)", ""},
        {"apa", "apa", "", "Apache languages", ""},
        {"ara", "ara", "ar", "Arabic", "Semitic"},
        {"arc", "arc", "", "Aramaic", ""},
        {"arn", "arn", "", "Araucanian", ""},
        {"arp", "arp", "", "Arapaho", ""},
        {"art", "art", "", "Artificial (Other)", ""},
        {"arw", "arw", "", "Arawak", ""},
        {"asm", "asm", "as", "Assamese", "Indian"},
        {"ath", "ath", "", "Athapascan languages", ""},
        {"aus", "aus", "", "Australian languages", ""},
        {"ava", "ava", "", "Avaric", ""},
        {"ave", "ave", "ae", "Avestan", ""},
        {"awa", "awa", "", "Awadhi", ""},
        {"aym", "aym", "ay", "Aymara", "Amerindian"},
        {"aze", "aze", "az", "Azerbaijani", "Turkic/altaic"},
        {"bad", "bad", "", "Banda", ""},
        {"bai", "bai", "", "Bamileke languages", ""},
        {"bak", "bak", "ba", "Bashkir", "Turkic/altaic"},
        {"bal", "bal", "", "Baluchi", ""},
        {"bam", "bam", "", "Bambara", ""},
        {"ban", "ban", "", "Balinese", ""},
        {"bas", "bas", "", "Basa", ""},
        {"bat", "bat", "", "Baltic (Other)", ""},
        {"bej", "bej", "", "Beja", ""},
        {"bel", "bel", "be", "Belarusian", "Slavic"},
        {"bem", "bem", "", "Bemba", ""},
        {"ben", "ben", "bn", "Bengali", "Indian"},
        {"ber", "ber", "", "Berber (Other)", ""},
        {"bho", "bho", "", "Bhojpuri", ""},
        {"bih", "bih", "bh", "Bihari", "Indian"},
        {"bik", "bik", "", "Bikol", ""},
        {"bin", "bin", "", "Bini", ""},
        {"bis", "bis", "bi", "Bislama", ""},
        {"bla", "bla", "", "Siksika", ""},
        {"bnt", "bnt", "", "Bantu (Other)", ""},
        {"bod", "tib", "bo", "Tibetan", "Asian"},
        {"bos", "bos", "bs", "Bosnian", ""},
        {"bra", "bra", "", "Braj", ""},
        {"bre", "bre", "br", "Breton", "Celtic"},
        {"btk", "btk", "", "Batak (Indonesia)", ""},
        {"bua", "bua", "", "Buriat", ""},
        {"bug", "bug", "", "Buginese", ""},
        {"bul", "bul", "bg", "Bulgarian", "Slavic"},
        {"cad", "cad", "", "Caddo", ""},
        {"cai", "cai", "", "Central American Indian (Other)", ""},
        {"car", "car", "", "Carib", ""},
        {"cat", "cat", "ca", "Catalan", "Romance"},
        {"cau", "cau", "", "Caucasian (Other)", ""},
        {"ceb", "ceb", "", "Cebuano", ""},
        {"cel", "cel", "", "Celtic (Other)", ""},
        {"ces", "cze", "cs", "Czech", "Slavic"},
        {"cha", "cha", "ch", "Chamorro", ""},
        {"chb", "chb", "", "Chibcha", ""},
        {"che", "che", "ce", "Chechen", ""},
        {"chg", "chg", "", "Chagatai", ""},
        {"chk", "chk", "", "Chuukese", ""},
        {"chm", "chm", "", "Mari", ""},
        {"chn", "chn", "", "Chinook jargon", ""},
        {"cho", "cho", "", "Choctaw", ""},
        {"chp", "chp", "", "Chipewyan", ""},
        {"chr", "chr", "", "Cherokee", ""},
        {"chu", "chu", "cu", "Church Slavic", ""},
        {"chv", "chv", "cv", "Chuvash", ""},
        {"chy", "chy", "", "Cheyenne", ""},
        {"cmc", "cmc", "", "Chamic languages", ""},
        {"cop", "cop", "", "Coptic", ""},
        {"cor", "cor", "kw", "Cornish", ""},
        {"cos", "cos", "co", "Corsican", "Romance"},
        {"cpe", "cpe", "", "Creoles and pidgins, English based (Other)", ""},
        {"cpf", "cpf", "", "Creoles and pidgins, French-based (Other)", ""},
        {"cpp", "cpp", "", "Creoles and pidgins, Portuguese-based (Other)", ""},
        {"cre", "cre", "", "Cree", ""},
        {"crp", "crp", "", "Creoles and pidgins (Other)", ""},
        {"cus", "cus", "", "Cushitic (Other)", ""},
        {"cym", "wel", "cy", "Welsh", "Celtic"},
        {"dak", "dak", "", "Dakota", ""},
        {"dan", "dan", "da", "Danish", "Germanic"},
        {"day", "day", "", "Dayak", ""},
        {"del", "del", "", "Delaware", ""},
        {"den", "den", "", "Slave (Athapascan)", ""},
        {"deu", "ger", "de", "Deutsch", "Germanic"},
        {"dgr", "dgr", "", "Dogrib", ""},
        {"din", "din", "", "Dinka", ""},
        {"div", "div", "", "Divehi", ""},
        {"doi", "doi", "", "Dogri", ""},
        {"dra", "dra", "", "Dravidian (Other)", ""},
        {"dua", "dua", "", "Duala", ""},
        {"dum", "dum", "", "Dutch, Middle (ca. 1050-1350)", ""},
        {"dyu", "dyu", "", "Dyula", ""},
        {"dzo", "dzo", "dz", "Dzongkha", "Asian"},
        {"efi", "efi", "", "Efik", ""},
        {"egy", "egy", "", "Egyptian (Ancient)", ""},
        {"eka", "eka", "", "Ekajuk", ""},
        {"ell", "gre", "el", "Greek, Modern (1453-)", "Latin/greek"},
        {"elx", "elx", "", "Elamite", ""},
        {"eng", "eng", "en", "Englisch", "Germanic"},
        {"enm", "enm", "", "English, Middle (1100-1500)", ""},
        {"epo", "epo", "eo", "Esperanto", "International aux."},
        {"est", "est", "et", "Estonian", "Finno-ugric"},
        {"eus", "baq", "eu", "Basque", "Basque"},
        {"ewe", "ewe", "", "Ewe", ""},
        {"ewo", "ewo", "", "Ewondo", ""},
        {"fan", "fan", "", "Fang", ""},
        {"fao", "fao", "fo", "Faroese", "Germanic"},
        {"fas", "per", "fa", "Persian", ""},
        {"fat", "fat", "", "Fanti", ""},
        {"fij", "fij", "fj", "Fijian", "Oceanic/indonesian"},
        {"fin", "fin", "fi", "Finnish", "Finno-ugric"},
        {"fiu", "fiu", "", "Finno-Ugrian (Other)", ""},
        {"fon", "fon", "", "Fon", ""},
        {"fra", "fre", "fr", "Franz�sisch", "Romance"},
        {"frm", "frm", "", "French, Middle (ca. 1400-1600)", ""},
        {"fro", "fro", "", "French, Old (842-ca. 1400)", ""},
        {"fry", "fry", "fy", "Frisian", "Germanic"},
        {"ful", "ful", "", "Fulah", ""},
        {"fur", "fur", "", "Friulian", ""},
        {"gaa", "gaa", "", "Ga", ""},
        {"gay", "gay", "", "Gayo", ""},
        {"gba", "gba", "", "Gbaya", ""},
        {"gem", "gem", "", "Germanic (Other)", ""},
        {"gez", "gez", "", "Geez", ""},
        {"gil", "gil", "", "Gilbertese", ""},
        {"gla", "gla", "gd", "Gaelic (Scots)", "Celtic"},
        {"gle", "gle", "ga", "Irish", "Celtic"},
        {"glg", "glg", "gl", "Gallegan", "Romance"},
        {"glv", "glv", "gv", "Manx", ""},
        {"gmh", "gmh", "", "German, Middle High (ca. 1050-1500)", ""},
        {"goh", "goh", "", "German, Old High (ca. 750-1050)", ""},
        {"gon", "gon", "", "Gondi", ""},
        {"gor", "gor", "", "Gorontalo", ""},
        {"got", "got", "", "Gothic", ""},
        {"grb", "grb", "", "Grebo", ""},
        {"grc", "grc", "", "Greek, Ancient (to 1453)", ""},
        {"grn", "grn", "gn", "Guarani", "Amerindian"},
        {"guj", "guj", "gu", "Gujarati", "Indian"},
        {"gwi", "gwi", "", "Gwich�in", ""},
        {"hai", "hai", "", "Haida", ""},
        {"hau", "hau", "ha", "Hausa", "Negro-african"},
        {"haw", "haw", "", "Hawaiian", ""},
        {"heb", "heb", "he", "Hebrew", ""},
        {"her", "her", "hz", "Herero", ""},
        {"hil", "hil", "", "Hiligaynon", ""},
        {"him", "him", "", "Himachali", ""},
        {"hin", "hin", "hi", "Hindi", "Indian"},
        {"hit", "hit", "", "Hittite", ""},
        {"hmn", "hmn", "", "Hmong", ""},
        {"hmo", "hmo", "ho", "Hiri Motu", ""},
        {"hrv", "scr", "hr", "Croatian", "Slavic"},
        {"hun", "hun", "hu", "Hungarian", "Finno-ugric"},
        {"hup", "hup", "", "Hupa", ""},
        {"hye", "arm", "hy", "Armenian", "Indo-european (other)"},
        {"iba", "iba", "", "Iban", ""},
        {"ibo", "ibo", "", "Igbo", ""},
        {"ijo", "ijo", "", "Ijo", ""},
        {"iku", "iku", "iu", "Inuktitut", ""},
        {"ile", "ile", "ie", "Interlingue", "International aux."},
        {"ilo", "ilo", "", "Iloko", ""},
        {"ina", "ina", "ia", "Interlingua (International Auxiliary Language Association)", "International aux."},
        {"inc", "inc", "", "Indic (Other)", ""},
        {"ind", "ind", "id", "Indonesian", ""},
        {"ine", "ine", "", "Indo-European (Other)", ""},
        {"ipk", "ipk", "ik", "Inupiaq", "Eskimo"},
        {"ira", "ira", "", "Iranian (Other)", ""},
        {"iro", "iro", "", "Iroquoian languages", ""},
        {"isl", "ice", "is", "Icelandic", "Germanic"},
        {"ita", "ita", "it", "Italian", "Romance"},
        {"jaw", "jav", "jw", "Javanese", ""},
        {"jpn", "jpn", "ja", "Japanese", "Asian"},
        {"jpr", "jpr", "", "Judeo-Persian", ""},
        {"kaa", "kaa", "", "Kara-Kalpak", ""},
        {"kab", "kab", "", "Kabyle", ""},
        {"kac", "kac", "", "Kachin", ""},
        {"kal", "kal", "kl", "Kalaallisut", "Eskimo"},
        {"kam", "kam", "", "Kamba", ""},
        {"kan", "kan", "kn", "Kannada", "Dravidian"},
        {"kar", "kar", "", "Karen", ""},
        {"kas", "kas", "ks", "Kashmiri", "Indian"},
        {"kat", "geo", "ka", "Georgian", "Ibero-caucasian"},
        {"kau", "kau", "", "Kanuri", ""},
        {"kaw", "kaw", "", "Kawi", ""},
        {"kaz", "kaz", "kk", "Kazakh", "Turkic/altaic"},
        {"kha", "kha", "", "Khasi", ""},
        {"khi", "khi", "", "Khoisan (Other)", ""},
        {"khm", "khm", "km", "Khmer", "Asian"},
        {"kho", "kho", "", "Khotanese", ""},
        {"kik", "kik", "ki", "Kikuyu", ""},
        {"kin", "kin", "rw", "Kinyarwanda", "Negro-african"},
        {"kir", "kir", "ky", "Kirghiz", "Turkic/altaic"},
        {"kmb", "kmb", "", "Kimbundu", ""},
        {"kok", "kok", "", "Konkani", ""},
        {"kom", "kom", "kv", "Komi", ""},
        {"kon", "kon", "", "Kongo", ""},
        {"kor", "kor", "ko", "Korean", "Asian"},
        {"kos", "kos", "", "Kosraean", ""},
        {"kpe", "kpe", "", "Kpelle", ""},
        {"kro", "kro", "", "Kru", ""},
        {"kru", "kru", "", "Kurukh", ""},
        {"kum", "kum", "", "Kumyk", ""},
        {"kur", "kur", "ku", "Kurdish", "Iranian"},
        {"kut", "kut", "", "Kutenai", ""},
        {"lad", "lad", "", "Ladino", ""},
        {"lah", "lah", "", "Lahnda", ""},
        {"lam", "lam", "", "Lamba", ""},
        {"lao", "lao", "lo", "Lao", "Asian"},
        {"lat", "lat", "la", "Latin", "Latin/greek"},
        {"lav", "lav", "lv", "Latvian", "Baltic"},
        {"lez", "lez", "", "Lezghian", ""},
        {"lin", "lin", "ln", "Lingala", "Negro-african"},
        {"lit", "lit", "lt", "Lithuanian", "Baltic"},
        {"lol", "lol", "", "Mongo", ""},
        {"loz", "loz", "", "Lozi", ""},
        {"ltz", "ltz", "lb", "Letzeburgesch", ""},
        {"lua", "lua", "", "Luba-Lulua", ""},
        {"lub", "lub", "", "Luba-Katanga", ""},
        {"lug", "lug", "", "Ganda", ""},
        {"lui", "lui", "", "Luiseno", ""},
        {"lun", "lun", "", "Lunda", ""},
        {"luo", "luo", "", "Luo (Kenya and Tanzania)", ""},
        {"lus", "lus", "", "lushai", ""},
        {"mad", "mad", "", "Madurese", ""},
        {"mag", "mag", "", "Magahi", ""},
        {"mah", "mah", "mh", "Marshall", ""},
        {"mai", "mai", "", "Maithili", ""},
        {"mak", "mak", "", "Makasar", ""},
        {"mal", "mal", "ml", "Malayalam", "Dravidian"},
        {"man", "man", "", "Mandingo", ""},
        {"map", "map", "", "Austronesian (Other)", ""},
        {"mar", "mar", "mr", "Marathi", "Indian"},
        {"mas", "mas", "", "Masai", ""},
        {"mdr", "mdr", "", "Mandar", ""},
        {"men", "men", "", "Mende", ""},
        {"mga", "mga", "", "Irish, Middle (900-1200)", ""},
        {"mic", "mic", "", "Micmac", ""},
        {"min", "min", "", "Minangkabau", ""},
        {"mis", "mis", "", "Miscellaneous languages", ""},
        {"mkd", "mac", "mk", "Macedonian", "Slavic"},
        {"mkh", "mkh", "", "Mon-Khmer (Other)", ""},
        {"mlg", "mlg", "mg", "Malagasy", "Oceanic/indonesian"},
        {"mlt", "mlt", "mt", "Maltese", "Semitic"},
        {"mnc", "mnc", "", "Manchu", ""},
        {"mni", "mni", "", "Manipuri", ""},
        {"mno", "mno", "", "Manobo languages", ""},
        {"moh", "moh", "", "Mohawk", ""},
        {"mol", "mol", "mo", "Moldavian", "Romance"},
        {"mon", "mon", "mn", "Mongolian", ""},
        {"mos", "mos", "", "Mossi", ""},
        {"mri", "mao", "mi", "Maori", "Oceanic/indonesian"},
        {"msa", "may", "ms", "Malay", "Oceanic/indonesian"},
        {"mul", "mul", "", "Multiple languages", ""},
        {"mun", "mun", "", "Munda languages", ""},
        {"mus", "mus", "", "Creek", ""},
        {"mwr", "mwr", "", "Marwari", ""},
        {"mya", "bur", "my", "Burmese", "Asian"},
        {"myn", "myn", "", "Mayan languages", ""},
        {"nah", "nah", "", "Nahuatl", ""},
        {"nai", "nai", "", "North American Indian", ""},
        {"nau", "nau", "na", "Nauru", ""},
        {"nav", "nav", "nv", "Navajo", ""},
        {"nbl", "nbl", "nr", "Ndebele, South", ""},
        {"nde", "nde", "nd", "Ndebele, North", ""},
        {"ndo", "ndo", "ng", "Ndonga", ""},
        {"nds", "nds", "", "Low German; Low Saxon; German, Low; Saxon, Low", ""},
        {"nep", "nep", "ne", "Nepali", "Indian"},
        {"new", "new", "", "Newari", ""},
        {"nia", "nia", "", "Nias", ""},
        {"nic", "nic", "", "Niger-Kordofanian (Other)", ""},
        {"niu", "niu", "", "Niuean", ""},
        {"nld", "dut", "nl", "Dutch", "Germanic"},
        {"nno", "nno", "nn", "Norwegian Nynorsk", ""},
        {"nob", "nob", "nb", "Norwegian Bokm�l", ""},
        {"non", "non", "", "Norse, Old", ""},
        {"nor", "nor", "no", "Norwegian", "Germanic"},
        {"nso", "nso", "", "Sotho, Northern", ""},
        {"nub", "nub", "", "Nubian languages", ""},
        {"nya", "nya", "ny", "Chichewa; Nyanja", ""},
        {"nym", "nym", "", "Nyamwezi", ""},
        {"nyn", "nyn", "", "Nyankole", ""},
        {"nyo", "nyo", "", "Nyoro", ""},
        {"nzi", "nzi", "", "Nzima", ""},
        {"oci", "oci", "oc", "Occitan (post 1500); Proven�al", "Romance"},
        {"oji", "oji", "", "Ojibwa", ""},
        {"ori", "ori", "or", "Oriya", "Indian"},
        {"orm", "orm", "om", "Oromo", "Hamitic"},
        {"osa", "osa", "", "Osage", ""},
        {"oss", "oss", "os", "Ossetian; Ossetic", ""},
        {"ota", "ota", "", "Turkish, Ottoman (1500-1928)", ""},
        {"oto", "oto", "", "Otomian languages", ""},
        {"paa", "paa", "", "Papuan (Other)", ""},
        {"pag", "pag", "", "Pangasinan", ""},
        {"pal", "pal", "", "Pahlavi", ""},
        {"pam", "pam", "", "Pampanga", ""},
        {"pan", "pan", "pa", "Panjabi", "Indian"},
        {"pap", "pap", "", "Papiamento", ""},
        {"pau", "pau", "", "Palauan", ""},
        {"peo", "peo", "", "Persian, Old (ca. 600-400 b.c.)", ""},
        {"phi", "phi", "", "Philippine (Other)", ""},
        {"pli", "pli", "pi", "Pali", ""},
        {"pol", "pol", "pl", "Polish", "Slavic"},
        {"pon", "pon", "", "Pohnpeian", ""},
        {"por", "por", "pt", "Portuguese", "Romance"},
        {"pra", "pra", "", "Prakrit languages", ""},
        {"pro", "pro", "", "Proven�al, Old (to 1500)", ""},
        {"pus", "pus", "ps", "Pushto", "Iranian"},
        {"que", "que", "qu", "Quechua", "Amerindian"},
        {"raj", "raj", "", "Rajasthani", ""},
        {"rap", "rap", "", "Rapanui", ""},
        {"rar", "rar", "", "Rarotongan", ""},
        {"roa", "roa", "", "Romance (Other)", ""},
        {"rom", "rom", "", "Romany", ""},
        {"ron", "rum", "ro", "Romanian", "Romance"},
        {"run", "run", "rn", "Rundi", "Negro-african"},
        {"rus", "rus", "ru", "Russian", "Slavic"},
        {"sad", "sad", "", "Sandawe", ""},
        {"sag", "sag", "sg", "Sango", "Negro-african"},
        {"sah", "sah", "", "Yakut", ""},
        {"sai", "sai", "", "South American Indian (Other)", ""},
        {"sal", "sal", "", "Salishan languages", ""},
        {"sam", "sam", "", "Samaritan Aramaic", ""},
        {"san", "san", "sa", "Sanskrit", "Indian"},
        {"sas", "sas", "", "Sasak", ""},
        {"sat", "sat", "", "Santali", ""},
        {"sco", "sco", "", "Scots", ""},
        {"sel", "sel", "", "Selkup", ""},
        {"sem", "sem", "", "Semitic (Other)", ""},
        {"sga", "sga", "", "Irish, Old (to 900)", ""},
        {"sgn", "sgn", "", "Sign Languages", ""},
        {"shn", "shn", "", "Shan", ""},
        {"sid", "sid", "", "Sidamo", ""},
        {"sin", "sin", "si", "Sinhalese", "Indian"},
        {"sio", "sio", "", "Siouan languages", ""},
        {"sit", "sit", "", "Sino-Tibetan (Other)", ""},
        {"sla", "sla", "", "Slavic (Other)", ""},
        {"slk", "slo", "sk", "Slovak", "Slavic"},
        {"slv", "slv", "sl", "Slovenian", "Slavic"},
        {"sme", "sme", "se", "Northern Sami", ""},
        {"smi", "smi", "", "Sami languages (Other)", ""},
        {"smo", "smo", "sm", "Samoan", "Oceanic/indonesian"},
        {"sna", "sna", "sn", "Shona", "Negro-african"},
        {"snd", "snd", "sd", "Sindhi", "Indian"},
        {"snk", "snk", "", "Soninke", ""},
        {"sog", "sog", "", "Sogdian", ""},
        {"som", "som", "so", "Somali", "Hamitic"},
        {"son", "son", "", "Songhai", ""},
        {"sot", "sot", "st", "Sotho, Southern", "Negro-african"},
        {"spa", "spa", "es", "Spanish", "Romance"},
        {"sqi", "alb", "sq", "Albanian", "Indo-european (other)"},
        {"srd", "srd", "sc", "Sardinian", ""},
        {"srp", "scc", "sr", "Serbian", "Slavic"},
        {"srr", "srr", "", "Serer", ""},
        {"ssa", "ssa", "", "Nilo-Saharan (Other)", ""},
        {"ssw", "ssw", "ss", "Swati", "Negro-african"},
        {"suk", "suk", "", "Sukuma", ""},
        {"sun", "sun", "su", "Sundanese", "Oceanic/indonesian"},
        {"sus", "sus", "", "Susu", ""},
        {"sux", "sux", "", "Sumerian", ""},
        {"swa", "swa", "sw", "Swahili", "Negro-african"},
        {"swe", "swe", "sv", "Swedish", "Germanic"},
        {"syr", "syr", "", "Syriac", ""},
        {"tah", "tah", "ty", "Tahitian", ""},
        {"tai", "tai", "", "Tai (Other)", ""},
        {"tam", "tam", "ta", "Tamil", "Dravidian"},
        {"tat", "tat", "tt", "Tatar", "Turkic/altaic"},
        {"tel", "tel", "te", "Telugu", "Dravidian"},
        {"tem", "tem", "", "Timne", ""},
        {"ter", "ter", "", "Tereno", ""},
        {"tet", "tet", "", "Tetum", ""},
        {"tgk", "tgk", "tg", "Tajik", "Iranian"},
        {"tgl", "tgl", "tl", "Tagalog", "Oceanic/indonesian"},
        {"tha", "tha", "th", "Thai", "Asian"},
        {"tig", "tig", "", "Tigre", ""},
        {"tir", "tir", "ti", "Tigrinya", "Semitic"},
        {"tiv", "tiv", "", "Tiv", ""},
        {"tkl", "tkl", "", "Tokelau", ""},
        {"tli", "tli", "", "Tlingit", ""},
        {"tmh", "tmh", "", "Tamashek", ""},
        {"tog", "tog", "", "Tonga (Nyasa)", ""},
        {"ton", "ton", "to", "Tonga (Tonga Islands)", "Oceanic/indonesian"},
        {"tpi", "tpi", "", "Tok Pisin", ""},
        {"tsi", "tsi", "", "Tsimshian", ""},
        {"tsn", "tsn", "tn", "Tswana", "Negro-african"},
        {"tso", "tso", "ts", "Tsonga", "Negro-african"},
        {"tuk", "tuk", "tk", "Turkmen", "Turkic/altaic"},
        {"tum", "tum", "", "Tumbuka", ""},
        {"tur", "tur", "tr", "Turkish", "Turkic/altaic"},
        {"tut", "tut", "", "Altaic (Other)", ""},
        {"tvl", "tvl", "", "Tuvalu", ""},
        {"twi", "twi", "tw", "Twi", "Negro-african"},
        {"tyv", "tyv", "", "Tuvinian", ""},
        {"uga", "uga", "", "Ugaritic", ""},
        {"uig", "uig", "ug", "Uighur", ""},
        {"ukr", "ukr", "uk", "Ukrainian", "Slavic"},
        {"umb", "umb", "", "Umbundu", ""},
        {"und", "und", "", "Undetermined", ""},
        {"urd", "urd", "ur", "Urdu", "Indian"},
        {"uzb", "uzb", "uz", "Uzbek", "Turkic/altaic"},
        {"vai", "vai", "", "Vai", ""},
        {"ven", "ven", "", "Venda", ""},
        {"vie", "vie", "vi", "Vietnamese", "Asian"},
        {"vol", "vol", "vo", "Volap�k", "International aux."},
        {"vot", "vot", "", "Votic", ""},
        {"wak", "wak", "", "Wakashan languages", ""},
        {"wal", "wal", "", "Walamo", ""},
        {"war", "war", "", "Waray", ""},
        {"was", "was", "", "Washo", ""},
        {"wen", "wen", "", "Sorbian languages", ""},
        {"wol", "wol", "wo", "Wolof", "Negro-african"},
        {"xho", "xho", "xh", "Xhosa", "Negro-african"},
        {"yao", "yao", "", "Yao", ""},
        {"yap", "yap", "", "Yapese", ""},
        {"yid", "yid", "yi", "Yiddish", ""},
        {"yor", "yor", "yo", "Yoruba", "Negro-african"},
        {"ypk", "ypk", "", "Yupik languages", ""},
        {"zap", "zap", "", "Zapotec", ""},
        {"zen", "zen", "", "Zenaga", ""},
        {"zha", "zha", "za", "Zhuang", ""},
        {"zho", "chi", "zh", "Chinese", "Asian"},
        {"znd", "znd", "", "Zande", ""},
        {"zul", "zul", "zu", "Zulu", "Negro-african"},
        {"zun", "zun", "", "Zuni", ""},
    };
