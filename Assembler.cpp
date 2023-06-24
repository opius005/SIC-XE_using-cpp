#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define s second
#define f first



string th = "3";
string BASE = "";
map<string, pair<int, string>> symtab;
vector<string> littab;
vector<string> oneIns(3, "");
vector<vector<string>> Ins(0, oneIns);
string startadr = "0";
string psize = "0";
string locctr = "0";
vector<string> pc;
bool error = false;
string T = "";
string tsadr = "";
string H = "";
ofstream fout;
ofstream eout;
ofstream lout;
vector<string> M;
vector<string> lit;
vector<string> EXTREF;
vector<string> EXTDEF;



///////////////////



map<char, string> bin;
map<string, char> tohex;
map<string, pair<int, string>> optab;
map<string, string> regtab;
void buildregtab()
{
  regtab["A"] = "0";
  regtab["X"] = "1";
  regtab["L"] = "2";
  regtab["PC"] = "8";
  regtab["B"] = "3";
  regtab["S"] = "4";
  regtab["T"] = "5";
  regtab["F"] = "6";
}
void buildoptab()
{
  optab["LDA"] = {3, "00"};
  optab["LDB"] = {3, "68"};
  optab["LDX"] = {3, "04"};
  optab["LDT"] = {3, "74"};
  optab["LDS"] = {3, "6C"};
  optab["ADD"] = {3, "18"};
  optab["TIX"] = {3, "2C"};
  optab["JLT"] = {3, "38"};
  optab["STA"] = {3, "0C"};
  optab["RSUB"] = {3, "4C"};

  optab["ADD"] = {3, "18"};
  optab["ADDF"] = {3, "58"};
  optab["ADDR"] = {2, "90"};
  optab["AND"] = {3, "40"};
  optab["CLEAR"] = {2, "B4"};
  optab["COMP"] = {3, "28"};
  optab["COMPF"] = {3, "88"};
  optab["COMPR"] = {2, "A0"};
  optab["DIV"] = {3, "24"};
  optab["DIVF"] = {3, "64"};

  optab["DIVR"] = {2, "9C"};
  optab["FIX"] = {1, "C4"};
  optab["FLOAT"] = {1, "C0"};
  optab["HIO"] = {1, "F4"};
  optab["J"] = {3, "3C"};
  optab["JEQ"] = {3, "30"};
  optab["JGT"] = {3, "34"};
  optab["JSUB"] = {3, "48"};
  optab["LDCH"] = {3, "50"};
  optab["LDF"] = {3, "70"};

  optab["LDL"] = {3, "08"};
  optab["LDS"] = {3, "6C"};
  optab["LDX"] = {3, "04"};
  optab["LDT"] = {3, "74"};
  optab["LDS"] = {3, "6C"};
  optab["LPS"] = {3, "D0"};
  optab["LDT"] = {3, "74"};
  optab["LDX"] = {3, "04"};
  optab["MUL"] = {3, "20"};
  optab["MULF"] = {3, "60"};

  optab["MULR"] = {2, "98"};
  optab["NORM"] = {1, "C8"};
  optab["OR"] = {3, "44"};
  optab["RD"] = {3, "D8"};
  optab["RMO"] = {2, "AC"};
  optab["RSUB"] = {3, "4C"};
  optab["SHIFTL"] = {2, "A4"};
  optab["SHIFTR"] = {2, "A8"};
  optab["SIO"] = {1, "F0"};
  optab["SSK"] = {3, "EC"};

  optab["STA"] = {3, "0C"};
  optab["STB"] = {3, "78"};
  optab["STCH"] = {3, "54"};
  optab["STF"] = {3, "80"};
  optab["STI"] = {3, "D4"};
  optab["STL"] = {3, "14"};
  optab["STS"] = {3, "7C"};
  optab["STSW"] = {3, "E8"};
  optab["STT"] = {3, "84"};
  optab["STX"] = {3, "10"};

  optab["SUB"] = {3, "1C"};
  optab["SUBF"] = {3, "5C"};
  optab["SUBR"] = {2, "94"};
  optab["SVC"] = {3, "B0"};
  optab["TD"] = {3, "E0"};
  optab["TIO"] = {1, "F8"};
  optab["TIX"] = {3, "2C"};
  optab["TIXR"] = {2, "B8"};
  optab["WD"] = {3, "DC"};
  optab["RSUB"] = {3, "4C"};
}
void buildbin()
{
  bin['0'] = "0000";
  bin['1'] = "0001";
  bin['2'] = "0010";
  bin['3'] = "0011";
  bin['4'] = "0100";
  bin['5'] = "0101";
  bin['6'] = "0110";
  bin['7'] = "0111";
  bin['8'] = "1000";
  bin['9'] = "1001";
  bin['A'] = "1010";
  bin['B'] = "1011";
  bin['C'] = "1100";
  bin['D'] = "1101";
  bin['E'] = "1110";
  bin['F'] = "1111";
}
void buildtohex()
{
  tohex["0000"] = '0';
  tohex["0001"] = '1';
  tohex["0010"] = '2';
  tohex["0011"] = '3';
  tohex["0100"] = '4';
  tohex["0101"] = '5';
  tohex["0110"] = '6';
  tohex["0111"] = '7';
  tohex["1000"] = '8';
  tohex["1001"] = '9';
  tohex["1010"] = 'A';
  tohex["1011"] = 'B';
  tohex["1100"] = 'C';
  tohex["1101"] = 'D';
  tohex["1110"] = 'E';
  tohex["1111"] = 'F';
}
bool isnum(string s)
{
  int c = 0;
  for (int i = 0; i < (int)s.size(); i++)
  {
    if (s[i] <= '9' && s[i] >= '0')
    {
      c++;
    }
  }
  if (c == (int)s.size())
  {
    return true;
  }
  else
  {
    return false;
  }
}
string to_hex(string s)
{
  if (!isnum(s))
  {
    cout << s << "j" << endl;
  }
  int s1 = stoi(s);
  bitset<24> b(s1);
  string bh = b.to_string();
  string h = "";
  for (int i = 0; i < 24; i += 4)
  {
    string sub = bh.substr(i, 4);
    h.push_back(tohex[sub]);
  }

  return h;
}
ll to_int(string n)
{
  string s = n;
  while (s.size() < 6)
  {
    s = "0" + s;
  }
  string a = "";
  for (int i = 0; i < (int)s.size(); i++)
  {
    a = a + bin[s[i]];
  }
  if (a[0] == '1')
  {
    bool tgl = false;
    for (ll i = 23; i >= 0; i--)
    {
      if (tgl)
      {
        if (a[i] == '1')
        {
          a[i] = '0';
        }
        else
        {
          a[i] = '1';
        }
      }
      if (a[i] == '1')
      {
        tgl = 1;
      }
    }
    bitset<24> b(a);
    ll ans = b.to_ulong();
    ans = ans * (-1);
    return ans;
  }
  else
  {
    bitset<24> b(a);
    ll ans = b.to_ulong();
    return ans;
  }
}
string add(string s1, string s2)
{
  ll f1 = to_int(s1);
  ll f2 = to_int(s2);
  // cout<<f1<<" "<<f2<<endl;
  f1 += f2;
  bitset<24> b3(f1);
  // cout<<b3<<endl;
  string f = b3.to_string();
  string h = "";
  for (int i = 0; i < 24; i += 4)
  {
    string sub = f.substr(i, 4);
    h += (tohex[sub]);
  }

  return h;
}
int comp(string s1, string s2)
{
  ll f1 = to_int(s1);
  ll f2 = to_int(s2);
  // cout<<f1<<" "<<f2<<endl;
  if (f1 == f2)
  {
    return 0;
  }
  if (f1 > f2)
  {
    return 1;
  }
  if (f1 < f2)
  {
    return 2;
  }
}
string sub(string s1, string s2)
{
  ll f1 = to_int(s1);
  ll f2 = to_int(s2);
  // cout<<f1<<" "<<f2<<endl;
  f1 -= f2;
  bitset<24> b3(f1);
  // cout<<b3<<endl;
  string f = b3.to_string();
  string h = "";
  for (int i = 0; i < 24; i += 4)
  {
    string sub = f.substr(i, 4);
    h.push_back(tohex[sub]);
  }

  return h;
}
string mul(string s1, string s2)
{
  ll f1 = to_int(s1);
  ll f2 = to_int(s2);
  // cout<<f1<<" "<<f2<<endl;
  f1 *= f2;
  bitset<24> b3(f1);
  // cout<<b3<<endl;
  string f = b3.to_string();
  string h = "";
  for (int i = 0; i < 24; i += 4)
  {
    string sub = f.substr(i, 4);
    h.push_back(tohex[sub]);
  }

  return h;
}
string div(string s1, string s2)
{
  ll f1 = to_int(s1);
  ll f2 = to_int(s2);
  // cout<<f1<<" "<<f2<<endl;
  f1 /= f2;
  // cout<<f1<<endl;
  bitset<24> b3(f1);
  // cout<<b3<<endl;
  string f = b3.to_string();
  string h = "";
  for (int i = 0; i < 24; i += 4)
  {
    string sub = f.substr(i, 4);
    h.push_back(tohex[sub]);
  }
  return h;
}
string decToHexa(int n)
{
  // char array to store hexadecimal number
  char hexaDeciNum[100];

  // counter for hexadecimal number array
  int i = 0;
  while (n != 0)
  {
    // temporary variable to store remainder
    int temp = 0;

    // storing remainder in temp variable.
    temp = n % 16;

    // check if temp < 10
    if (temp < 10)
    {
      hexaDeciNum[i] = temp + 48;
      i++;
    }
    else
    {
      hexaDeciNum[i] = temp + 55;
      i++;
    }

    n = n / 16;
  }

  string ans = "";

  // printing hexadecimal number array in reverse order
  for (int j = i - 1; j >= 0; j--)
    ans += hexaDeciNum[j];

  return ans;
}
// Function to convert ASCII to HEX
string HEX(string ascii)
{
  // Initialize final String
  string hex = "";

  // Make a loop to iterate through
  // every character of ascii string
  for (int i = 0; i < ascii.length(); i++)
  {
    // Take a char from
    // position i of string
    char ch = ascii[i];

    // Cast char to integer and
    // find its ascii value
    int tmp = (int)ch;

    // Change this ascii value
    // integer to hexadecimal value
    string part = decToHexa(tmp);

    // Add this hexadecimal value
    // to final string.
    hex += part;
  }

  // Return the final
  // string hex
  return hex;
}





//////////////////////////




void writedrec()
{
  string D = "";
  for (int i = 0; i < EXTDEF.size(); i += 2)
  {
    string ex = EXTDEF[i];
    while (ex.size() < 6)
    {
      ex = ex + " ";
    }
    if ((D.size() + 12) > 72)
    {
      fout << "D" << D << endl;
      D = "";
    }
    else
    {
      D = D + ex + EXTDEF[i + 1];
    }
  }
  if (D != "")
  {
    fout << "D" << D << endl;
  }
}
void writerrec()
{
  string R;
  for (int i = 0; i < EXTREF.size(); i++)
  {
    string ex = EXTREF[i];
    while (ex.size() < 6)
    {
      ex = ex + " ";
    }
    if ((R.size() + 6) > 72)
    {
      fout << "R" << R << endl;
      R = "";
    }
    else
    {
      R = R + ex;
    }
  }
  if (R != "")
  {
    fout << "R" << R << endl;
    R = "";
  }
}
void writetrec()
{
  if (T == "")
    return;
  fout << "T";
  fout << tsadr;
  fout << to_hex(to_string(T.size() / 2)).substr(4, 2);
  fout << T << endl;
  T = "";
}
void writemrec()
{
  for (int i = 0; i < (int)M.size(); i++)
  {
    fout << M[i] << endl;
  }
}
void writelistfile(int InsNum, string obj)
{
  lout << pc[InsNum] << " " << Ins[InsNum][0] << " " << Ins[InsNum][1] << " ";
  lout << Ins[InsNum][2] << " " << obj << endl;
}
pair<string, int> evaluate_expression(string exp, int InsNum)
{
  // cout<<exp<<endl;
  if (exp == "*")
  {
    pair<string, int> p = {pc[InsNum], 1};
    return p;
  }
  int pre = 1;
  string em = "";
  pair<string, int> emp = {em, -1};
  string term = "";
  vector<pair<string, int>> terms;
  for (int i = 0; i < exp.size(); i++)
  {
    if (exp[i] == '+')
    {
      terms.push_back({term, pre});
      pre = 1;
      term = "";
      continue;
    }
    if (exp[i] == '-')
    {
      terms.push_back({term, pre});
      pre = -1;
      term = "";
      continue;
    }
    if (exp[i] == '*')
    {
      if (isnum(term))
      {
        pre *= stoi(term);
      }
      else
      {
        eout << "Invalid Expression" << exp << endl;
        return emp;
      }
      term = "";
      continue;
    }
    if (exp[i] == '/')
    {
      eout << "Invalid Expression" << exp << endl;
      return emp;
    }

    term.push_back(exp[i]);
    if (i == exp.size() - 1)
    {
      terms.push_back({term, pre});
    }
  }
  int rel = 0;
  for (int i = 0; i < terms.size(); i++)
  {
    if (!(isnum(terms[i].f)))
    {
      rel += ((symtab[terms[i].f].f) * (terms[i].s));
    }
  }
  bool hasextref = false;
  // cout<<rel<<" "<<exp<<" "<<endl;
  string val;
  for (int i = 0; i < terms.size(); i++)
  {
    int ab = abs(terms[i].s);
    int sign = terms[i].s / ab;
    string termval = to_hex(to_string(ab));
    if (symtab[terms[i].f].s != "")
    {
      termval = mul(termval, (symtab[terms[i].f].s));
    }
    else
    {
      if (isnum(terms[i].f))
      {
        termval = mul(termval, to_hex(terms[i].f));
      }
      else
      {
        bool isextref = false;
        int j = 0;
        for (j = 0; j < EXTREF.size(); j++)
        {
          if (EXTREF[j] == terms[i].f)
          {
            string mod = "M";
            if (Ins[InsNum][1] == "WORD")
            {
              mod = mod + pc[InsNum] + "06";
            }
            else
            {
              if (Ins[InsNum][1][0] == '+')
              {
                mod = mod + add(pc[InsNum], "1") + "05";
              }
              else
              {
                mod = mod + add(pc[InsNum], "1") + "03";
              }
            }
            if (sign == 1)
            {
              mod = mod + "+";
            }
            else
            {
              mod = mod + "-";
            }
            mod = mod + EXTREF[j];
            hasextref = true;
            isextref = true;
            M.push_back(mod);
            break;
          }
        }
        if (isextref)
        {
          termval = "0";
        }
        else
        {
          error = true;
          eout << "symbol not found  " << terms[i].f << endl;
          return emp;
        }
      }
    }
    if (sign == -1)
    {
      val = sub(val, termval);
    }
    else
    {
      val = add(val, termval);
    }
  }
  pair<string, int> p = {val, rel};
  // cout<<val<<endl;

  if ((rel == 0 || rel == 1) || hasextref)
  {
    return p;
  }
  else
  {
    eout << "Invalid Expression " << exp << endl;
    return emp;
  }
  // return emp;
}
void Pass_1()
{
  cout << "Pass1" << endl;
  string b = "3";
  for (int i = 0; i < (int)Ins.size(); i++)
  {
    if (Ins[i][1] == "START")
    {
      startadr = Ins[i][2];
      while (startadr.size() < 6)
      {
        startadr = "0" + startadr;
      }
      locctr = startadr;
      continue;
      // cout<<locctr<<endl;
    }
    // cout<<locctr<<" ";
    pc[i] = locctr;

    // cout<<Ins[i][0]<<" "<<Ins[i][1]<<" "<<Ins[i][2]<<endl;
    if (Ins[i][1] != "END" && Ins[i][1] != "CSECT")
    {
      if ((Ins[i][1] != ".") && (Ins[i][0] != "."))
      {
        if (Ins[i][0] != "")
        {
          if (symtab[Ins[i][0]].s != "")
          {
            eout << "Duplicate label" << Ins[i][0] << endl;
            error = true;
          }
          else
          {
            symtab[Ins[i][0]].s = locctr;
          }
        }
        if (Ins[i][2] != "")
        {
          if (Ins[i][2][0] == '=')
          {
            lit.push_back(Ins[i][2]);
          }
        }
        if (Ins[i][1][0] == '+')
        {
          // cout<<Ins[i][0]<<endl;
          string si = to_string(4);
          string mod = "M" + add(locctr, "1") + "05";
          M.push_back(mod);
          locctr = add(locctr, si);
          continue;
        }
        if (optab[Ins[i][1]].f)
        {
          string si = to_string(optab[Ins[i][1]].f);
          locctr = add(locctr, si);
        }
        else
        {
          if ((Ins[i][1] == "RESW") || (Ins[i][1] == "RESB") || (Ins[i][1] == "WORD") || (Ins[i][1] == "BYTE"))
          {
            if (Ins[i][1] == "RESW")
            {
              locctr = add(locctr, mul(th, to_hex(Ins[i][2])));
            }
            if (Ins[i][1] == "RESB")
            {
              locctr = add(locctr, to_hex(Ins[i][2]));
            }
            if (Ins[i][1] == "WORD")
            {
              locctr = add(locctr, th);
            }
            if (Ins[i][1] == "BYTE")
            {
              if (Ins[i][2][0] == 'X')
              {
                int le = Ins[i][2].size() - 3;
                int k = le / 2 + le % 2;
                locctr = add(locctr, to_hex(to_string(k)));
              }
              else
              {
                locctr = add(locctr, to_hex(to_string(Ins[i][2].size() - 3)));
              }
            }
          }
          else
          {
            while (1)
            {
              if (Ins[i][1] == "BASE")
              {
                break;
              }
              if (Ins[i][1] == "LTORG")
              {
                for (int j = 0; j < (int)lit.size(); j++)
                {
                  if (symtab[lit[j]].s == "")
                  {
                    littab.push_back(lit[j]);
                    symtab[lit[j]].s = locctr;
                    int ls = lit[j].size() - 4;
                    if (lit[j][1] == 'X')
                    {
                      ls /= 2;
                    }
                    locctr = add(locctr, to_hex(to_string(ls)));
                  }
                }
                lit.clear();
                break;
              }
              if (Ins[i][1] == "EQU")
              {
                string exp = Ins[i][2];
                if (exp[0] == '#')
                {
                  exp = exp.substr(1, exp.size() - 1);
                }
                pair<string, int> val = evaluate_expression(exp, i);
                if (val.f != "")
                {
                  symtab[Ins[i][0]].s = val.f;
                  symtab[Ins[i][0]].f = val.s;
                }
                break;
              }
              if (Ins[i][1] == "EXTREF")
              {
                string e = "";
                for (int j = 0; j < Ins[i][2].size(); j++)
                {
                  if (Ins[i][2][j] == ' ' || Ins[i][2][j] == ',')
                  {
                    EXTREF.push_back(e);
                    e = "";
                  }
                  else
                  {
                    e.push_back(Ins[i][2][j]);
                  }
                }
                if (e != "")
                {
                  EXTREF.push_back(e);
                }
                break;
              }
              if (Ins[i][1] == "EXTDEF")
              {
                break;
              }
              if (Ins[i][1] == "CSECT")
              {
                break;
              }
              // if(Ins[i][1]=="ORG"){
              //   if(ORG==""){

              //   }
              // }

              error = true;
              eout << "Invalid Opcode " << Ins[i][1] << endl;
              break;
            }
          }
        }
      }
    }
    else
    {
      for (int j = 0; j < (int)lit.size(); j++)
      {
        if (symtab[lit[j]].s == "")
        {
          littab.push_back(lit[j]);
          symtab[lit[j]].s = locctr;

          int ls = lit[j].size() - 4;
          if (lit[j][1] == 'X')
          {
            ls /= 2;
          }
          locctr = add(locctr, to_hex(to_string(ls)));
        }
      }
      lit.clear();
    }
  }
  psize = sub(locctr, startadr);
  // cout<<psize<<endl;
}
void Pass_2()
{
  bool ismain = false;
  string obj[(int)Ins.size()];
  int lt = 0;
  string n = "H" + H;
  while (n.size() < 7)
  {
    n = n + " ";
  }
  if (n.size() > 7)
  {
    eout << "Program name size >6" << endl;
  }
  fout << n << startadr << psize << endl;

  tsadr = startadr;
  for (int i = 0; i < (int)Ins.size(); i++)
  {
    // cout<<pc[i]<<endl;
    obj[i] = "";
    if (Ins[i][1] == "START")
    {
      ismain = true;
      continue;
    }
    if (Ins[i][1] != "END" && Ins[i][1] != "CSECT")
    {
      if ((Ins[i][1] != ".") && (Ins[i][0] != "."))
      {
        string nxtpc = pc[i];
        int j = i;
        while (sub(nxtpc, pc[i]) == "000000")
        {
          j++;
          nxtpc = pc[j];
        }
        if (Ins[i][2] != "")
        {
          if (Ins[i][2][0] == '=')
          {
            lit.push_back(Ins[i][2]);
          }
        }
        string xbpe = "0";
        string disp = "000";
        // fout<<T<<endl;
        if (optab[Ins[i][1]].f == 3)
        {
          // cout<<Ins[i][1]<<endl;
          obj[i] = optab[Ins[i][1]].s;
          if (Ins[i][2] != "")
          {
            if (Ins[i][2][0] == '@')
            {
              obj[i] = add(obj[i], "2").substr(4, 2);
              // return;
              string oprd = Ins[i][2].substr(1, Ins[i][2].size() - 1);
              pair<string, int> p = evaluate_expression(oprd, i);
              if (p.f != "")
              {
                disp = sub(p.f, nxtpc);
              }
              else
              {
                error = true;
                eout << "Operand Not Found" << endl;
              }
              bool bs = 0;
              if (disp[0] == 'F')
              {
                string du = sub(nxtpc, p.f);
                if (comp(du, to_hex("2049")) != 2)
                {
                  if (BASE != "")
                  {
                    if (comp(BASE, p.f) == 1)
                    {
                      error = true;
                      eout << "Displacement out of bounds" << endl;
                    }
                    else
                    {
                      disp = sub(symtab[oprd].s, BASE);
                      if (comp(disp, "1000") != 2)
                      {
                        error = true;
                        eout << "Displacement out of bounds" << endl;
                      }
                      else
                      {
                        bs = 1;
                      }
                    }
                  }
                  else
                  {
                    error = true;
                    eout << "Displacement out of bounds" << endl;
                  }
                }
              }
              else
              {
                if (comp(disp, to_hex("2048")) != 2)
                {
                  if (BASE != "")
                  {
                    if (comp(BASE, symtab[oprd].s) == 1)
                    {
                      error = true;
                      eout << "Displacement out of bounds" << endl;
                    }
                    else
                    {
                      disp = sub(symtab[oprd].s, BASE);
                      if (comp(disp, "1000") != 2)
                      {
                        error = true;
                        eout << "Displacement out of bounds" << endl;
                      }
                      else
                      {
                        bs = 1;
                      }
                    }
                  }
                  else
                  {
                    error = true;
                    eout << "Displacement out of bounds" << endl;
                  }
                }
              }
              if (bs)
              {
                xbpe = add(xbpe, "4");
              }
              else
              {
                xbpe = add(xbpe, "2");
              }
              obj[i] = obj[i] + xbpe.substr(5, 1) + disp.substr(disp.size() - 3, 3);
            }
            else
            {
              if (Ins[i][2][0] == '#')
              {
                obj[i] = add(obj[i], "1").substr(4, 2);
                disp = Ins[i][2].substr(1, Ins[i][2].size() - 1);
                bool islabel = true;
                int co = 0;
                for (int it = 0; it < (int)disp.size(); it++)
                {
                  if (((disp[it] - '0') >= 0) && ((disp[it] - '0') < 10))
                  {
                    co++;
                  }
                }

                if (co == (int)disp.size())
                {

                  islabel = false;
                }
                if (islabel)
                {
                  pair<string, int> p = evaluate_expression(disp, i);
                  if (p.f != "")
                  {
                    disp = p.f;
                  }
                  else
                  {
                    error = true;
                    eout << "label " << disp << " not found" << endl;
                  }
                }
                else
                {
                  disp = to_hex(disp);
                }
                if (comp(disp, "1000") != 2)
                {
                  error = true;
                  eout << "Displacement out of bounds" << endl;
                }
                obj[i] = obj[i] + xbpe + disp.substr(disp.size() - 3, 3);
              }
              else
              {
                obj[i] = add(obj[i], "3").substr(4, 2);
                string oprd = Ins[i][2];
                if (oprd.substr(oprd.size() - 2, 2) == ",X")
                {
                  xbpe = add(xbpe, "8");
                  oprd = oprd.substr(0, oprd.size() - 2);
                }
                // cout<<oprd<<" ";
                pair<string, int> p = evaluate_expression(oprd, i);
                // cout<<p.f<<endl;
                if (p.f != "")
                {
                  disp = sub(p.f, nxtpc);
                }
                else
                {
                  error = true;
                  eout << "Operand Not Found" << endl;
                }
                bool bs = 0;
                if (disp[0] == 'F')
                {
                  string du = sub(nxtpc, p.f);
                  if (comp(du, to_hex("2049")) != 2)
                  {
                    if (BASE != "")
                    {
                      if (comp(BASE, p.f) == 1)
                      {
                        error = true;
                        eout << "Displacement out of bounds" << endl;
                      }
                      else
                      {
                        disp = sub(symtab[oprd].s, BASE);
                        if (comp(disp, "1000") != 2)
                        {
                          error = true;
                          eout << "Displacement out of bounds" << endl;
                        }
                        else
                        {
                          bs = 1;
                        }
                      }
                    }
                    else
                    {
                      error = true;
                      eout << "Displacement out of bounds" << endl;
                    }
                  }
                }
                else
                {
                  if (comp(disp, to_hex("2048")) != 2)
                  {
                    if (BASE != "")
                    {
                      if (comp(BASE, symtab[oprd].s) == 1)
                      {
                        error = true;
                        eout << "Displacement out of bounds" << endl;
                      }
                      else
                      {
                        disp = sub(symtab[oprd].s, BASE);
                        if (comp(disp, "1000") != 2)
                        {
                          error = true;
                          eout << "Displacement out of bounds" << endl;
                        }
                        else
                        {
                          bs = 1;
                        }
                      }
                    }
                    else
                    {
                      error = true;
                      eout << "Displacement out of bounds" << endl;
                    }
                  }
                }
                if (bs)
                {
                  xbpe = add(xbpe, "4");
                }
                else
                {
                  xbpe = add(xbpe, "2");
                }
                xbpe = add(xbpe, "0");
                obj[i] = obj[i] + xbpe.substr(5, 1) + disp.substr(disp.size() - 3, 3);
              }
            }
          }
          else
          {
            obj[i] = "4F0000";
          }

          // cout<<pc[i]<<" "<<obj[i]<<endl;
          if (T == "")
          {
            tsadr = pc[i];
          }

          if (T.size() + obj[i].size() > 60)
          {
            writetrec();
            tsadr = pc[i];
            cout << pc[i] << " " << Ins[i][1] << endl;
          }
          T = T + obj[i];
          writelistfile(i, obj[i]);
        }
        else
        {
          if (optab[Ins[i][1]].f)
          {
            if (optab[Ins[i][1]].f == 2)
            {
              obj[i] = optab[Ins[i][1]].s;
              if (Ins[i][2].size() == 1)
              {
                obj[i] = obj[i] + regtab[Ins[i][2]] + "0";
              }
              else
              {
                obj[i] = obj[i] + regtab[Ins[i][2].substr(0, 1)] + regtab[Ins[i][2].substr(2, 1)];
              }
              // cout<<pc[i]<<" "<<obj[i]<<endl;

              if (T == "")
              {
                tsadr = pc[i];
              }
              if (T.size() + obj[i].size() > 60)
              {
                writetrec();
                tsadr = pc[i];
                cout << pc[i] << " " << Ins[i][1] << endl;
              }
              T = T + obj[i];
            }
            if (optab[Ins[i][1]].f == 1)
            {
              obj[i] = optab[Ins[i][1]].s;
            }
            writelistfile(i, obj[i]);
          }
          else
          {
            string f4;
            if ((Ins[i][1][0] == '+') && Ins.size() > 1)
            {
              f4 = Ins[i][1].substr(1, Ins[i][1].size() - 1);
            }

            if (((Ins[i][1][0] == '+')) && (optab[f4].f == 3))
            {
              obj[i] = optab[f4].s;
              xbpe = add(xbpe, "1");
              if (Ins[i][2][0] == '@')
              {
                obj[i] = add(obj[i], "1");
                string oprd = Ins[i][2].substr(1, Ins[i][2].size() - 1);
                pair<string, int> p = evaluate_expression(oprd, i);
                if (p.f != "")
                {
                  disp = p.f;
                }
                else
                {
                  error = true;
                  eout << "Operand Not Found" << endl;
                }
              }
              else
              {
                if (Ins[i][2][0] == '#')
                {
                  obj[i] = add(obj[i], "1");
                  string oprd = Ins[i][2].substr(1, Ins[i][2].size() - 1);
                  bool islabel = true;
                  int co = 0;
                  for (int it = 0; it < (int)disp.size(); it++)
                  {
                    if (((disp[i] - '0') >= 0) && ((disp[i] - '0') < 10))
                    {
                      co++;
                    }
                  }
                  if (co == (int)disp.size())
                  {
                    islabel = false;
                  }
                  if (islabel)
                  {
                    pair<string, int> p = evaluate_expression(oprd, i);
                    if (p.f != "")
                    {
                      disp = p.f;
                    }
                    else
                    {
                      error = true;
                      eout << "Operand Not Found" << endl;
                    }
                  }
                  else
                  {
                    disp = to_hex(disp);
                  }
                  if (comp(disp, "100000") != 2)
                  {
                    error = true;
                    eout << "Displacement out of bounds" << endl;
                  }
                }
                else
                {
                  obj[i] = add(obj[i], "3");
                  string oprd = Ins[i][2];
                  if (oprd.substr(oprd.size() - 2, 2) == ",X")
                  {
                    xbpe = add(xbpe, "8");
                    oprd = oprd.substr(0, oprd.size() - 2);
                    // cout<<oprd<<endl;
                  }
                  pair<string, int> p = evaluate_expression(oprd, i);
                  if (p.f != "")
                  {
                    disp = p.f;
                  }
                  else
                  {
                    error = true;
                    eout << "Operand Not Found" << endl;
                  }
                }
              }
              obj[i] = obj[i].substr(4, 2) + xbpe.substr(5, 1) + disp.substr(1, 5);
              // cout<<pc[i]<<" "<<obj[i]<<endl;
              if (T == "")
              {
                tsadr = pc[i];
              }

              if (T.size() + obj[i].size() > 60)
              {
                writetrec();
                tsadr = pc[i];
                cout << pc[i] << " " << Ins[i][1] << endl;
              }
              T = T + obj[i];
              writelistfile(i, obj[i]);
            }
            else
            {
              if (Ins[i][1] == "BYTE")
              {
                if (Ins[i][2][0] == 'X')
                {
                  obj[i] = Ins[i][2].substr(2, Ins[i][2].size() - 3);
                }
                else
                {
                  string ch = Ins[i][2];
                  ch = ch.substr(2, Ins[i][2].size() - 3);
                  string ne = "";
                  for (int it = 0; it < ch.size(); it++)
                  {
                    int y = (int)ch[it];
                    ne = ne + decToHexa(y);
                  }
                  obj[i] = ne;
                }
                // cout<<obj[i]<<" "<<endl;

                if (T == "")
                {
                  tsadr = pc[i];
                }
                if (T.size() + obj[i].size() > 60)
                {
                  writetrec();
                  tsadr = pc[i];
                  cout << pc[i] << " " << Ins[i][1] << endl;
                }
                T = T + obj[i];
                writelistfile(i, obj[i]);
              }
              else
              {
                while (1)
                {
                  if (Ins[i][1] == "WORD")
                  {
                    pair<string, int> p = evaluate_expression(Ins[i][2], i);
                    string wrd = p.f;
                    if (comp(wrd, "1000000") != 2)
                    {
                      eout << "WORD constant not of word size " << wrd << endl;
                    }
                    else
                    {
                      obj[i] = p.f;

                      // cout<<Ins[i][0]<<" "<<pc[i]<<" "<<obj[i]<<endl;
                      if (T == "")
                      {
                        tsadr = pc[i];
                      }

                      if (T.size() + obj[i].size() > 60)
                      {
                        writetrec();
                        tsadr = pc[i];
                        cout << pc[i] << " " << Ins[i][1] << endl;
                      }
                      T = T + obj[i];
                      writelistfile(i, obj[i]);
                    }
                    break;
                  }
                  if (Ins[i][1] == "BASE")
                  {
                    BASE = symtab[Ins[i][2]].s;
                    break;
                  }
                  if (Ins[i][1] == "LTORG")
                  {
                    string loc = pc[i];
                    while ((lt < (int)littab.size()) && (comp(symtab[littab[lt]].s, nxtpc) != 1))
                    {
                      lout << "* " << littab[lt] << " " << loc << endl;
                      string ne = "";
                      if (littab[lt][1] == 'X')
                      {
                        ne = littab[lt].substr(3, littab[lt].size() - 4);
                      }
                      else
                      {
                        string ch = littab[lt];
                        ch = ch.substr(3, littab[lt].size() - 4);

                        for (int it = 0; it < ch.size(); it++)
                        {
                          int y = (int)ch[it];
                          ne = ne + decToHexa(y);
                        }
                      }

                      if (T == "")
                      {
                        tsadr = loc;
                      }
                      if (T.size() + ne.size() > 60)
                      {
                        writetrec();
                        tsadr = loc;
                        cout << loc << endl;
                      }
                      T = T + ne;
                      lt++;
                      ll si = ne.size() / 2 + ne.size() % 2;
                      loc = add(loc, to_hex(to_string(si)));
                    }
                    break;
                  }
                  if (Ins[i][1] == "RESW" || Ins[i][1] == "RESB")
                  {
                    writetrec();
                    break;
                  }
                  if (Ins[i][1] == "EQU")
                  {
                    break;
                  }

                  if (Ins[i][1] == "EXTDEF")
                  {
                    string e = "";
                    for (int j = 0; j < Ins[i][2].size(); j++)
                    {
                      if (Ins[i][2][j] == ' ' || Ins[i][2][j] == ',')
                      {
                        if (symtab[e].s == "")
                        {
                          eout << "EXTDEF symbol not in this control section " << e << endl;
                          e = "";
                        }
                        else
                        {
                          EXTDEF.push_back(e);
                          EXTDEF.push_back(symtab[e].s);
                          e = "";
                        }
                      }
                      else
                      {
                        e.push_back(Ins[i][2][j]);
                      }
                    }
                    if (e != "")
                    {
                      if (symtab[e].s == "")
                      {
                        eout << "EXTDEF symbol not in this control section " << e << endl;
                        e = "";
                      }
                      else
                      {
                        EXTDEF.push_back(e);
                        EXTDEF.push_back(symtab[e].s);
                        e = "";
                      }
                    }
                    writedrec();

                    break;
                  }
                  if (Ins[i][1] == "EXTREF")
                  {
                    writerrec();
                    break;
                  }
                  if (Ins[i][1] == "CSECT")
                  {
                    break;
                  }
                  error = true;
                  eout << "Invalid Opcode " << Ins[i][1] << endl;
                  break;
                }
              }
            }
          }
        }
      }
    }
    else
    {
      string loc = pc[i];
      loc = pc[i];
      while ((lt < (int)littab.size()) && (comp(symtab[littab[lt]].s, pc[i]) != 1))
      {
        lout << "* " << littab[lt] << " " << loc << endl;
        string ne = "";
        if (littab[lt][1] == 'X')
        {
          ne = littab[lt].substr(3, littab[lt].size() - 4);
        }
        else
        {
          string ch = littab[lt];
          ch = ch.substr(3, littab[lt].size() - 4);

          for (int it = 0; it < ch.size(); it++)
          {
            int y = (int)ch[it];
            ne = ne + decToHexa(y);
          }
        }
        if (T == "")
        {
          tsadr = loc;
        }

        if (T.size() + ne.size() > 60)
        {
          writetrec();
          tsadr = loc;
          cout << loc << endl;
        }
        T = T + ne;
        lt++;
        ll si = ne.size() / 2 + ne.size() % 2;
        loc = add(loc, to_hex(to_string(si)));
      }

      writetrec();
      writemrec();
      if (ismain)
      {
        fout << "E" << startadr << endl;
      }
      else
      {
        fout << "E" << endl;
      }
    }
  }
}
int main()
{
  fout.open("objpro.txt");
  eout.open("errors.txt");
  lout.open("listing_file.txt");
  // fout.erase();
  buildbin();
  buildtohex();
  buildoptab();
  writetrec();
  buildregtab();
  ifstream input("input.txt");
  string I;
  int j = 0;
  while (getline(input, I))
  {
    // cout<<I<<endl;
    pc.push_back("0");
    vector<string> v;
    string s = "";
    for (int i = 0; i < I.size(); i++)
    {
      if (I[i] == ' ' || I[i] == '\t')
      {
        if (s != "")
        {
          v.push_back(s);
          s = "";
        }
      }
      else
      {
        s.push_back(I[i]);
      }
    }
    if (s != "")
    {
      v.push_back(s);
    }
    // cout<<v.size()<<endl;
    if (v.size() == 3)
    {
      Ins.push_back({v[0], v[1], v[2]});
      // cout<<Ins[0][1]<<endl;
    }
    if (v.size() == 2)
    {
      if ((optab[v[1]].f) || (v[1] == "CSECT"))
      {
        Ins.push_back({v[0], v[1], ""});
      }
      else
      {
        Ins.push_back({"", v[0], v[1]});
      }
    }
    if (v.size() == 1)
    {
      Ins.push_back({"", v[0], ""});
    }

    int i = Ins.size() - 1;
    // cout<<Ins[i][1]<<endl;
    if (Ins[i][1] == "START")
    {

      H = Ins[i][0];
    }
    if (Ins[i][1] == "CSECT" || Ins[i][1] == "END")
    {
      vector<string> C = {Ins[i][0], Ins[i][1], Ins[i][2]};
      Pass_1();
      if (error)
      {
        cout << "ERROR" << endl;
      }
      Pass_2();
      symtab.clear();
      Ins.clear();
      H = Ins[i][0];
      locctr = "000000";
      M.clear();
      EXTDEF.clear();
      EXTREF.clear();
      littab.clear();
      lit.clear();
    }
  }
  return 0;
}
