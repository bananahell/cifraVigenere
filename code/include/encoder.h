#include <string>

#define LOWER_TO_UPPER 'a' - 'A'
#define ALPHABET_SIZE 26

/**
 * This function encodes a message given a key using Vigenere's cipher.
 * @param message Message to be encoded.
 * @param key Key used to encode the message, used in repetition.
 * @return Encoded message.
 */
std::string encode(const std::string&, const std::string&);

char vigEncode(char, const std::string&, int);
