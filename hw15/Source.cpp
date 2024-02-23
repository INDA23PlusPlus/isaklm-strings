#include <string>
#include <sstream>
#include <iostream>
#include <vector>


void string_matching()
{
	std::stringstream output;

	while(true)
	{
		std::string pattern;
		std::string text;

		if ((std::getline(std::cin, pattern) && std::getline(std::cin, text)) == false)
		{
			break;
		}


		if (pattern.length() <= text.length())
		{
			for (int i = 0; i <= text.length() - pattern.length(); ++i)
			{
				bool match = true;

				for (int j = 0; j < pattern.length(); ++j)
				{
					if (text[i + j] != pattern[j])
					{
						match = false;

						break;
					}
				}

				if (match)
				{
					output << i << " ";
				}
			}
		}

		output << '\n';
	}

	std::cout << output.str();
}

uint64_t modular_power(uint64_t x, uint64_t n, uint64_t m)
{
	uint64_t ans = 1;

	if(n > 0)
	{
		uint64_t square_root = modular_power(x, n / 2, m);

		ans = square_root * square_root;

		if (n & 1)
		{
			ans *= x;
		}
	}

	return ans % m;
}

uint64_t compute_hash(uint64_t start, uint64_t end, std::string& string)
{
	uint64_t ans = 0;

	for (uint64_t i = start; i < end; ++i)
	{
		ans += modular_power(string[i], i - start + 1, UINT64_MAX);

		ans %= UINT64_MAX;
	}

	return ans;
}

void string_hashing()
{
	std::stringstream output;


	std::string string;

	std::getline(std::cin, string);
	
	uint64_t queries;


	std::cin >> queries;

	for (uint64_t i = 0; i < queries; ++i)
	{
		uint64_t start;
		uint64_t end;

		std::cin >> start;
		std::cin >> end;


		output << compute_hash(start, end, string) << '\n';
	}

	std::cout << output.str();
}

void radio_transmission()
{
	int message_length;
	std::cin >> message_length;
	std::cin.ignore();

	char* message = (char*)malloc(message_length * sizeof(char));
	std::cin.getline(message, message_length + 1);


	int substring_length = 1;

	int substring_index = 0;

	for (int i = 1; i < message_length; ++i)
	{
		if (message[substring_index % substring_length] != message[i])
		{
			substring_length += (substring_index + 1);
			substring_index = 0;
		}
		else
		{
			++substring_index;
		}
	}

	std::cout << substring_length;
}

void chasing_subs()
{
	std::string message;
	std::string fragment;

	std::getline(std::cin, message);
	std::getline(std::cin, fragment);

	std::string substring(fragment.length(), ' ');


	std::vector<char> character_table1(26, ' ');
	std::vector<char> character_table2(26, ' ');

	bool found_substring = false;

	int match_count = 0;


	for (int i = 0; i <= message.length() - fragment.length(); ++i)
	{
		bool match = true;

		for (int j = 0; j < fragment.length(); ++j)
		{
			char message_char = message[i + j];
			char fragment_char = fragment[j];

			int table_index1 = message_char - 'a';
			int table_index2 = fragment_char - 'a';
			
			
			if (character_table2[table_index2] == ' ' && character_table1[table_index1] == ' ')
			{
				character_table2[table_index2] = message_char;
				character_table1[table_index1] = fragment_char;
			}
			else if (character_table2[table_index2] != message_char)
			{
				match = false;

				break;
			}


			if (!found_substring)
			{
				substring[j] = message_char;
			}
		}

		if (match)
		{
			++match_count;

			found_substring = true;
		}

		for (int j = 0; j < 26; ++j)
		{
			character_table1[j] = ' ';
			character_table2[j] = ' ';
		}
	}


	if (match_count == 1)
	{
		std::cout << substring;
	}
	else
	{
		std::cout << match_count;
	}
}


int main()
{
	//string_matching();
	//string_hashing();
	//radio_transmission();
	chasing_subs();
}