#include <iostream>
#include <string>    
#include <fstream>
using namespace std;
int n;
int p_c1[56] = { 57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34,
                 26, 18, 10, 2,  59, 51, 43, 35, 27, 19, 11, 3,
                 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,
                 62, 54, 46, 38, 30, 22, 14, 6,  61, 53, 45, 37,
                 29, 21, 13, 5,  28, 20, 12, 4 };

int p_c2[48] = { 14, 17, 11, 24, 1,  5,  3,  28,
                 15, 6,  21, 10, 23, 19, 12, 4,
                 26, 8,  16, 7,  27, 20, 13, 2,
                 41, 52, 31, 37, 47, 55, 30, 40,
                 51, 45, 33, 48, 44, 49, 39, 56,
                 34, 53, 46, 42, 50, 36, 29, 32 };

int init_p[64] = { 58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44,
                   36, 28, 20, 12, 4,  62, 54, 46, 38, 30, 22,
                   14, 6,  64, 56, 48, 40, 32, 24, 16, 8,  57,
                   49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35,
                   27, 19, 11, 3,  61, 53, 45, 37, 29, 21, 13,
                   5,  63, 55, 47, 39, 31, 23, 15, 7 };

int inv_p[64]= { 40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47,
                 15, 55, 23, 63, 31, 38, 6,  46, 14, 54, 22,
                 62, 30, 37, 5,  45, 13, 53, 21, 61, 29, 36,
                 4,  44, 12, 52, 20, 60, 28, 35, 3,  43, 11,
                 51, 19, 59, 27, 34, 2,  42, 10, 50, 18, 58,
                 26, 33, 1,  41, 9,  49, 17, 57, 25 };

int exp_[48] = { 32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
                8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

int per[32] = { 16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
                26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
                3,  9, 19, 13, 30, 6,  22, 11, 4,  25 };
int sbox_arr[8][4][16]={
    {
       {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
       {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
       {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
       {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
   },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};
uint64_t get_bits(uint64_t bits, uint8_t pos, uint64_t mask)
{
    return (bits >> pos) & mask;
}
uint64_t set_bit_original (uint64_t bits, uint8_t pos, uint8_t value)
{
   uint64_t mask = 1LL << (63 - pos);
   if (value)
       bits |= mask;
   else
       bits &= ~mask;
   return bits;
}
uint64_t sbox(uint64_t x){
    uint64_t res = 0;
    int sbox_input[8];
    uint64_t sbox_output[8];
    int temp = 0;
    int i = 0;
    while(temp <= 42){
        sbox_input[i] = get_bits(x,temp,0b111111);
        temp+=6;
        i++;
    }
    int index = 7;
    int w = 0;
    for(int i = 0; i < size(sbox_input); i++){
        int x = sbox_input[i];
        uint8_t row1 = get_bits(x, 5, 1);
        uint8_t row2 = get_bits(x, 0, 1);
        uint64_t col = get_bits(x, 1, 0b1111);
        uint64_t row = 0;
        row = set_bit_original(row, 63, row2);
        row = set_bit_original(row, 62, row1);
        sbox_output[i] = sbox_arr[index][row][col];
        res = res | (sbox_output[i] << w);
        w+=4;
        index--;
    }
    return res;
}

uint64_t xor_logic (uint64_t a, uint64_t b){
    return a ^ b;
}

uint64_t shift_left_1(uint64_t a){
    uint64_t res = get_bits(a, 0, 0xfffffff);
    res = res << 1;
    res = res | get_bits(res, 28, 0b1);
    res = res & 0xffffffefffffff;
//    res = set_bit(res, 63, get_bits(res, 28, 0b1));
//    res = set_bit(res, 35, 0);
    return res;
}

uint64_t shift_left_2(uint64_t a){
    uint64_t res = shift_left_1(a);
    res = shift_left_1(res);
    return res;
}
//
uint64_t set_bit(uint64_t bits, uint8_t pos, uint8_t value)
{
   uint64_t mask = 1LL << pos;
   if (value)
       bits |= mask;
   else
       bits &= ~mask;
   return bits;
}
// set specific bits at position = pos with certain value = value
uint64_t set_bits(uint64_t bits, uint8_t pos, uint64_t value)
{
    uint64_t mask = value << pos;
    bits |= mask;
    return bits;
}
// convert one digit in hex to decimal or binary
uint64_t onehexa2Bin(char hexa)
{
    if (hexa == '0') return 0;
    else if (hexa == '1') return 1;
    else if (hexa == '2') return 2;
    else if (hexa == '3') return 3;
    else if (hexa == '4') return 4;
    else if (hexa == '5') return 5;
    else if (hexa == '6') return 6;
    else if (hexa == '7') return 7;
    else if (hexa == '8') return 8;
    else if (hexa == '9') return 9;
    else if (hexa == 'A' || hexa == 'a') return 10;
    else if (hexa == 'B' || hexa == 'b') return 11;
    else if (hexa == 'C' || hexa == 'c') return 12;
    else if (hexa == 'D' || hexa == 'd') return 13;
    else if (hexa == 'E' || hexa == 'e') return 14;
    else if (hexa == 'F' || hexa == 'f') return 15;
    
}
// convert hex number to decimal or binary
uint64_t hexa2Bin(string hexa_num)
{
    uint64_t output = 0;
    int pos = 0;
    int size = hexa_num.size();
    for (int i = 0; i < size; i++)
    {
        uint64_t num = onehexa2Bin(hexa_num[size - i - 1]);
        output = set_bits(output, pos, num);
        pos = pos + 4;
    }
    return output;
}

// des permutation
uint64_t permutation(int permutation_arr[], uint64_t plaintext, int in, int size)
{
    uint64_t output = 0;
    int d = 64 - in;
    for (int i = 0; i < size; i++)
    {
        int index = get_bits(plaintext, 64 - permutation_arr[i] - d, 0b1);
        output = set_bit(output, size - 1 - i, index);
    }
    return output;
}

// convert hex text to array of 64-bit sequence
uint64_t* read(string content)
{
    // size of 64-bit numbers
    int content_size = content.size();
    n = (4 * content_size) / 64;
    // array of 64-bit numbers
    uint64_t* plaintext = new  uint64_t[n];
    int j = 0;
    int k = 0;
    string num ="";
    // fill the array of 64-bit numbers
    for (int i = 0; i< content_size; i++)
    {
        num = num + content[i];
        k++;
        if (k == 16)
        {
            k = 0;
            plaintext[j] = hexa2Bin(num);
            num = "";
            j++;
        }
    }
    return plaintext;
}
char hex_table(uint64_t n) {
    if (n == 0) return '0';
    else if (n == 1) return '1';
    else if (n == 2) return '2';
    else if (n == 3) return '3';
    else if (n == 4) return '4';
    else if (n == 5) return '5';
    else if (n == 6) return '6';
    else if (n == 7) return '7';
    else if (n == 8) return '8';
    else if (n == 9) return '9';
    else if (n == 10) return 'A';
    else if (n == 11) return 'B';
    else if (n == 12) return 'C';
    else if (n == 13) return 'D';
    else if (n == 14) return 'E';
    else if (n == 15) return 'F';
    
}

string convert_to_hex(uint64_t num) {
    string hex = "";
    for (int i = 60; i > -1; i--) {
        hex += hex_table(get_bits(num, i, 0b1111));
        i = i - 3;
    }
    return hex;
}

void output_file(string path, string out) {
    string p;
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '\\') {
            p = path + "\\output.txt";
            break;
        }
        else if (path[i] == '/') {
            p = path + "/output.txt";
            break;
        
        }

    }
    cout << p << endl;
    ofstream output;
    output.open(p);
    if (output.is_open())
    {
        output << out;

        output.close();
    }
    else cout << "File opening is fail";
}
uint64_t* keys(uint64_t key) {
    //cout << key << endl;
    static uint64_t keys[16];
    uint64_t pc1= permutation(p_c1,key,64,56);
    //cout << "pc1  " << pc1 << endl;
    uint64_t key_right = get_bits(pc1, 0, 0xfffffff);
    //cout << "key_right  " << key_right << endl;
    uint64_t key_left = get_bits(pc1, 28, 0xfffffff);
    //cout << "key_left  " << key_left << endl;
    
    for (int i = 1; i < 17; i++) {
        if ((i == 1) || (i == 2) || (i == 9) || (i == 16)) {
            key_right = shift_left_1(key_right);
            key_left = shift_left_1(key_left);
        }
        else {
            key_right = shift_left_2(key_right);
            key_left = shift_left_2(key_left);
        }
        //cout << "key_right  " <<i<<":   " << key_right << endl;
       // cout << "key_left  " << i << ":   " << key_left << endl;
        uint64_t key_con= (key_right|(key_left << 28));
        //cout << "key_con  " << i << ":   " << key_con << endl;
        uint64_t key_round= permutation(p_c2, key_con, 56,48);
        //cout << "key_round  " << i << ":   " << key_round << endl;
        keys[i-1] = key_round;

    }
    return keys;
}
uint64_t* decrp_keys(uint64_t key) {
    uint64_t* k = keys(key);
    static uint64_t rkeys[16];
    for (int i = 0; i < 16; i++) {
        rkeys[i] = k[15 - i];
    }
    return rkeys;
}

uint64_t f_function(uint64_t n, uint64_t k) {
    uint64_t n_exp= permutation(exp_, n,32, 48);
    //cout << "n_exp  " << ":   " << n_exp << endl;
    uint64_t n_xor = xor_logic(n_exp, k);
    //cout << "n_xor  " << ":   " <<k<<"    " << n_xor << endl;
    uint64_t n_sbox = sbox(n_xor);
   // cout << "n_sbox  " << ":   " << n_sbox << endl;
    return permutation(per, n_sbox, 32,32);
}

uint64_t des(uint64_t seq, uint64_t key,int t) {
    uint64_t* keys_;
    if (t == 0) keys_ = keys(key);
    else keys_ = decrp_keys(key);
    //cout << "------------" << endl;
    uint64_t seq_ip= permutation(init_p, seq, 64,64);
    //cout << "seq_ip  " << ":   " << seq_ip << endl;
    uint64_t p_right= get_bits(seq_ip, 0, 0xffffffff);
    //cout << "p_right  " << ":   " << p_right << endl;
    uint64_t p_left = get_bits(seq_ip, 32, 0xffffffff);
    //cout << "p_left  " << ":   " << p_left << endl;
    for (int i = 1; i < 17; i++) {
        uint64_t lt = p_left;
        p_left = p_right;
        //cout << "f_fn  " << ":   " << f_function(p_right, keys_[i - 1]) << endl;
       // cout << "key " << i << ":   " << keys_[i - 1] << endl;
        p_right = xor_logic(lt, f_function(p_right, keys_[i - 1]));
       // cout << p_left << " ......    " << p_right << "tl: " <<lt << endl;
       // cout << "round " << i << ":  " << (p_right | (p_left << 32));
    }

    uint64_t seq_swap = (p_left | (p_right << 32));
    
    return permutation(inv_p, seq_swap, 64,64);
}
//
int main(int argc,char* argv[])
{
    // check validation
    if (argc < 4)
    {
        return 1;
    }
    // input path
    string in_path = argv[1];
    //key
    string k = argv[2];
    uint64_t key = hexa2Bin(k);
    // output path
    string out_path = argv[3];
    // Create a text string, which is used to output the text file
    string content;
    string text;

    // Read from the text file
    ifstream MyReadFile(in_path); //filename.txt

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, text)) {
        // append text to content
        content = content + text;
    }

    //arrays of 64-bit numbers
    uint64_t* plaintext = read(content);    
    // Close the file
    MyReadFile.close();

    return 0;
}
