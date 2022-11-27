#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "decipherer.h"
#include "encoder.h"

#define USER_QUIT 0
#define USER_GET_PASS_SIZE 1
#define USER_GET_BEST_PASS 2
#define USER_USE_OWN_PASS 3

using namespace std;

int main() {
  string message =
      "Be patient till the last. Romans, countrymen, and lovers! hear me for "
      "my cause, and be silent, that you may hear: believe me for mine honour, "
      "and have respect to mine honour, that you may believe: censure me in "
      "your wisdom, and awake your senses, that you may the better judge. If "
      "there be any in this assembly, any dear friend of Caesar's, to him I "
      "say, that Brutus' love to Caesar was no less than his. If then that "
      "friend demand why Brutus rose against Caesar, this is my answer: —Not "
      "that I loved Caesar less, but that I loved Rome more. Had you rather "
      "Caesar were living and die all slaves, than that Caesar were dead, to "
      "live all free men? As Caesar loved me, I weep for him; as he was "
      "fortunate, I rejoice at it; as he was valiant, I honour him: but, as he "
      "was ambitious, I slew him. There is tears for his love; joy for his "
      "fortune; honour for his valour; and death for his ambition. Who is here "
      "so base that would be a bondman? If any, speak; for him have I "
      "offended. Who is here so rude that would not be a Roman? If any, speak; "
      "for him have I offended. Who is here so vile that will not love his "
      "country? If any, speak; for him have I offended. I pause for a reply. "
      "Then none have I offended. I have done no more to Caesar than you shall "
      "do to Brutus. The question of his death is enrolled in the Capitol; his "
      "glory not extenuated, wherein he was worthy, nor his offences enforced, "
      "for which he suffered death. Here comes his body, mourned by Mark "
      "Antony: who, though he had no hand in his death, shall receive the "
      "benefit of his dying, a place in the commonwealth; as which of you "
      "shall not? With this I depart,—that, as I slew my best lover for the "
      "good of Rome, I have the same dagger for myself, when it shall please "
      "my country to need my death.";
  string key = "Brutus";

  vector<string> encodedMessages = encode(message, key);
  vector<string> decipheredMessages;
  map<int, int>::iterator it;
  string tryingKey;

  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "message: " << endl << message << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "key: " << key << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "raw encoded message: " << endl << encodedMessages[0] << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "encoded with symbols: " << endl << encodedMessages[1] << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;

  map<int, int> sizeLikeliness = getMostLikelyPassSize(encodedMessages[0]);
  cout << "sizeLikeliness:" << endl;
  for (it = sizeLikeliness.begin(); it != sizeLikeliness.end(); ++it) {
    cout << "(" << it->first << ", " << it->second << ")" << endl;
  }

  cout << "Choose a key with which to decipher the encoded message: ";
  cin >> tryingKey;
  decipheredMessages = decipherWithKey(encodedMessages[1], tryingKey);

  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "deciphered with symbols: " << endl << decipheredMessages[1] << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;

  return 0;
}

// Encoded messages:

// CVJTNAFENMCDMKBXFSTKLHGSOJWHOFUISFYFBEXEINFIMAYSSDYYIJNPWTOKFRHWVWTZFXHLUYUMS
// GVDURBWBIVXFAFMYFYXPIGBHWIFHHOJBEXAUNFIYLJWDKNHGAOVBHHGVINAULZFOFUQCVFBYNFTYG
// MMSVGXCFZFOKQATUIFUFERQTEWZFOKMWOJYLNZBKSHOEBPNAYTFKNXLBVUAXCXUYYKYTFRHRCFUYC
// LUKTVGUFQBESWYSSWLBYFEFZVUWTRLLNGIZGBMSZKBTNTSLNNMDPMYMIUBVMTLOBJHHFWTJNAUFIZ
// MBZLIVHMBSUWLBYFEUYFUFENBRVJVKOLLGTVUZUAOJNVUWTRLMBATZMFSSOJQXLFPKNAULJCIOYVD
// RYLUJMVMLVMUKBTNAMFPXXJPDYFIJFYUWSGVIUMBWSTUXMSSNYKYDJMCGASOUXBYSMCMEUNFJNAUF
// UYUMWSFJUKQWSVXXUVUFFBPWBCFYLWFDYGUKDRYLUJMFPXXEFZQXYHGFLACEBJBXQSTWIKNMORNXC
// JFAIBWWBKCMUKIVQTMNBCCTHLJYIGIMSYCFVMURMAYOBJUFVAUZINMATCYPBANKBXLWJJNXUJTWIK
// BATCIOYBPPZHLZJJZHLLVEYAIFPLLYIJIZMOUDPLLTHVEVUMBXPIBBMSNSCMCGONBHCKIVLXMGCRM
// XNZBKQHODESYTVGOUGTHAGRHRMHFREYIJIZGAUNFZIYZWOUYWQZPZMAYJFJIKOVFKBTNOPLFWHGUS
// YTLGNRHBZSOPMIYSLWIKBANYUOYAPWZXHVFUQAIATYYKYKPMCEYLIRNPCDMEIMFGWVBBMUPLHMLQJ
// WUGSKQVUDZGSYCFBSWVCHZXFEXXXAQROLYXPIUKYHMPNAYFOFHXBSWVCHZXFEXXXAIRPXXGOVHHGG
// SVNHWSFJUKNZBESHOKIRFEXGUFVKOLVJNAYIVVMMCGOFZACKEVUMBATVHKIDMVXBHLIVWTJAUFFAC
// KHCIKSFPKYQNWOLUMYVXYYKYAOYYPUKXFLMBQOFLACKPWZXHUFJYGZGSTYWZGSNBBWZIVMNZXFIYW
// XWBKBAYJFTIFYKIZMUIVZDINLFFUVRGSSBUGNGOPQAILIFOZBZFYUWHGIRHWCFIZMWYSUYMAUDMIY
// VYAWVNAYTFEYYCLPWBBMVZZHZUHMRWXCFUYYVIENFHPYSMKBTMOIZWAIXZFOLBSMCHHNOJKBMBATZ
// XXJSSKNAULBJCLFWXDSUYKUCIOYJGFLMBWHFIWIXSFGXCZBMYMBWTRGXXSHXYKZGSDSLYDGNBXHAU
// JBTFDQCYTMWNPWHOFUISMIFFVXFSVFRNA

// CV JTNAFEN MCDM KBX FSTK. LHGSOJ, WHOFUISFYF, BEX EINFIM! AYSS DY YIJ NP
// WTOKF, RHW VW TZFXHL, UYUM SGV DUR BWBI: VXFAFMY FY XPI GBHW IFHHOJ, BEX AUNF
// IYLJWDK NH GAOV BHHGVI, NAUL ZFO FUQ CVFBYNF: TYGMMSV GX CF ZFOK QATUIF, UFE
// RQTEW ZFOK MWOJYL, NZBK SHO EBP NAY TFKNXL BVUAX. CX UYYKY TF RHR CF UYCL
// UKTVGUFQ, BES WYSS WLBYFE FZ VUWTRL'L, NG IZG B MSZ, KBTN TSLNNM' DPMY MI
// UBVMTL OBJ HH FWTJ NAUF IZM. BZ LIVH MBSU WLBYFE UYFUFE NBR VJVKOL LGTV
// UZUAOJN VUWTRL, MBAT ZM FS SOJQXL: —FPK NAUL J CIOYV DRYLUJ MVML, VMU KBTN A
// MFPXX JPDY FIJF. YUW SGV IUMBWS TUXMSS NYKY DJMCGA SOU XBY SMC MEUNFJ, NAUF
// UYUM WSFJUK QWSV XXUV, UF FBPW BCF YLWF DYG? UK DRYLUJ MFPXX EF, Z QXYH GFL
// ACE; BJ BX QST WIKNMORNX, C JFAIBWW BK CM; UK IV QTM NBCCTHL, J YIGIMS YCF:
// VMU, RM AY OBJ UFVAUZINM, A TCYP BAN. KBXLW JJ NXUJT WIK BAT CIOY; BPP ZHL
// ZJJ ZHLLVEY; AIFPLL YIJ IZM OUDPLL; THV EVUMB XPI BBM SNSCMCGO. NBH CK IVLX
// MG CRMX NZBK QHODE SY T VGOUGTH? AG RHR, MHFRE; YIJ IZG AUNF Z IYZWOUYW. QZP
// ZM AYJF JI KOVF KBTN OPLFW HGU SY T LGNRH? BZ SOP, MIYSL; WIK BAN YUOY A
// PWZXHVFU. QAI AT YYKY KP MCEY LIRN PCDM EIM FGWV BBM UPLHMLQ? JW UGS, KQVUD;
// ZGS YCF BSWV C HZXFEXXX. A QROLY XPI U KYHMP. NAYF OFHX BSWV C HZXFEXXX. A
// IRPX XGOV HH GGSV NH WSFJUK NZBE SHO KIRFE XG UF VKOLVJ. NAY IVVMMCGO FZ ACK
// EVUMB AT VHKIDMVX BH LIV WTJAUFF; ACK HCIKS FPK YQNWOLUMYV, XYYKYAO YY PUK
// XFLMBQ, OFL ACK PWZXHUFJ YGZGSTYW, ZGS NBBWZ IV MNZXFIYW XWBKB. AYJF TIFYK
// IZM UIVZ, DINLFFU VR GSSB UGNGOP: QAI, LIFOZB ZF YUW HG IRHW CF IZM WYSUY,
// MAUDM IYVYAWV NAY TFEYYCL PW BBM VZZHZ, U HMRWX CF UYY VIENFHPYSMKB; TM OIZWA
// IX ZFO LBSMC HHN? OJKB MBAT Z XXJSSK,—NAUL, BJ C LFWX DS UYKU CIOYJ GFL MBW
// HFIW IX SFGX, C ZBMY MBW TRGX XSHXYK ZGS DSLYDG, NBXH AU JBTFD QCYTMW NP
// WHOFUIS MI FFVX FS VFRNA.
