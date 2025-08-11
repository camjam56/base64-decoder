#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string input_b64;

std::string base64_code = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


//ASCII
// 0->9 = 48->57
// A->Z = 65->90
// a->z = 97->122
// + = 43
// / = 47
void b64_decode(std::string input_b64){

	std::vector<int> index_out(input_b64.size());

	for (int i = 0; i < input_b64.size(); i++){

		char target_char = input_b64[i];
		auto it = std::find(base64_code.begin(), base64_code.end(), target_char);

		if (it != base64_code.end()){
			int index = std::distance(base64_code.begin(), it);
			index_out[i] = index;
			std::cout << index << "\n";
		}

	}
}


int main() {
	
	std::cin >> input_b64;
	b64_decode(input_b64);
	return 1;
}

