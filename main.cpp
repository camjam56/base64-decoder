#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

std::string input_b64;
std::string base64_code = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int pad_count = 0;

void ascii_to_string(std::vector<int> ascii_in){

	std::string output;
	for (int i = 0; i < ascii_in.size(); i++){
		output.push_back(static_cast<char>(ascii_in[i]));
	}
	std::cout << output << "\n"; 
}


void bit8_to_int(std::vector<std::string> bit8_input){

	// Int to indicate the bytes to leave off the end due to padding
	// Used for for loop range
	int real_bytes = bit8_input.size() - pad_count;


	std::vector<int> int_out(real_bytes);


	for(int i = 0; i < real_bytes; i++){
		for(int j = 0; j < 8; j++){
			if (bit8_input[i][j] == '1'){
				int_out[i] += pow(2, 7-j);
			}
		}
	}

	ascii_to_string(int_out);
}


void bit6_to_bit8(std::string bit6_input){

	// Concatenate trailing zeros
	int trail_zero = bit6_input.size() % 8;

	if (trail_zero != 0){
		for (int i = 0; i < 8 - trail_zero; i++){
			bit6_input += '0';
		}
	}

	int bytes = bit6_input.size()/8;
	std::vector<std::string> bit8_out(bytes);

	for (int i = 0; i < bytes; i++){
		for (int j = 0; j < 8; j++){
			bit8_out[i] += bit6_input[j + 8*i];
		}
	}

	bit8_to_int(bit8_out);
}

void indice_to_6bitbinary(std::vector<int> index_in){

	std::string binary_out;
	for (int i = 0; i < index_in.size(); i++){
		int binary_buffer = 0;
		int decimal_buffer  = index_in[i];

		// Converting decimal of each index to binary
		for (int n = 0; n < 8; n++){
			if (decimal_buffer >= pow(2, 7-n)){
				binary_buffer += 1*pow(10, 7-n);
				decimal_buffer -= pow(2, 7-n);
			}
		}

		 
		std::string str_bin_buf = std::to_string(binary_buffer);

		if (str_bin_buf.size() != 6){
			while(str_bin_buf.size() != 6){
				str_bin_buf = '0' + str_bin_buf;
			}
		}	
		binary_out += str_bin_buf;
	}

	bit6_to_bit8(binary_out);
}


void base64_to_indice(std::string input_b64){
	
	// Defining index_out, a vector of int values that are the indices of each character
	std::vector<int> index_out(input_b64.size());

	// For loop to cycle each base64 char
	for (int i = 0; i < input_b64.size(); i++){

		char target_char = input_b64[i];

		// If the char is padding, ignore it but add to pad count
		if (target_char == '='){
			pad_count ++;
		}
		// Else, find it in the map string and assign the index
		else{
			auto it = std::find(base64_code.begin(), base64_code.end(), target_char);

			if (it != base64_code.end()){
				int index = std::distance(base64_code.begin(), it);
				index_out[i] = index;
			}
		}
	}
	
	// Call function with index_out as a parameter
	indice_to_6bitbinary(index_out);
}






int main() {
	
	std::cin >> input_b64;
	base64_to_indice(input_b64);
	return 1;
}

