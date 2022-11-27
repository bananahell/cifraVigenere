#ifndef ENCODER
#define ENCODER

#include <string>
#include <vector>

#define LOWER_TO_UPPER 'a' - 'A'
#define ALPHABET_SIZE 26

/**
 * This function encodes a message given a key using Vigenere's cipher.
 * @param message Message to be encoded.
 * @param key Key used to encode the message, used in repetition.
 * @return Encoded messages - first is raw, second has symbols.
 */
std::vector<std::string> encode(const std::string&, const std::string&);

/**
 * Encodes letter in a position of a message with a key using Vigenere's cipher.
 * @param oldLetter Letter of the message to be encoded.
 * @param key Key used to encode the message, used in repetition.
 * @param messageIndex Letter's position in the message.
 * @return Letter encoded in Vigenere's cipher.
 */
char vigEncode(char, const std::string&, int);

#endif  // ENCODER
