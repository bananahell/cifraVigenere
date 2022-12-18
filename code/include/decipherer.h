#ifndef DECIPHERER
#define DECIPHERER

#include <map>
#include <string>
#include <vector>

#define LOWER_TO_UPPER 'a' - 'A'
#define ALPHABET_SIZE 26

#define ENGLISH 0
#define PORTUGUESE 1

/**
 * Finds the best password size to decipher this encoded message looking into
 * substring frequencies (Kasiski's method).
 * @param encodedMessage Message to be deciphered.
 * @return Map with number of all substring distances among themselves.
 */
std::map<int, int> getMostLikelyPassSize(std::string);

/**
 * Using a key, deciphers a Vigenere encoded message.
 * @param encodedSymbol Encoded message with symbols other than just letters.
 * @param key Key thought to be the one that encoded the message.
 * @return Deciphered messages - first is raw, second has symbols.
 */
std::vector<std::string> decipherWithKey(const std::string&,
                                         const std::string&);

/**
 * Decodes letter in a position of a message with a key using Vigenere's cipher.
 * @param oldLetter Letter of the message to be decoded.
 * @param key Key thought to be used to encode the message, used in repetition.
 * @param messageIndex Letter's position in the message.
 * @return Letter decoded in Vigenere's cipher.
 */
char vigDecipher(char, const std::string&, int);

std::vector<std::vector<double>> getEncodedMsgFreq(int keySize, std::string encodedMessage);

#endif  // DECIPHERER
