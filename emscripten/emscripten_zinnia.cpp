#include <iostream>
#include <string.h>
#include <emscripten.h>
#include "../zinnia/zinnia.h"

bool InitRecog(const char* dictFile, int width, int height);
void ExitRecog();
const char* CharacterRecognize(const int* strokes);

int main(int argc, char **argv) {
  if (!InitRecog("zh_Hans.model", 300, 300)) {
    return -1;
  }
  
  int input[] = {243, 273, 393, 450, -1, 0, 700, 253, 343, 486, 280, 716, 393, 866, 710, 880, -1, -1};
  const char* result = CharacterRecognize(input);
  if (strlen(result) > 0) {
    std::cout << CharacterRecognize(input) << std::endl;
    std::cout << "Test succeeded!" << std::endl;
  } else {
    std::cout << "Test failed.!" << std::endl;
  }

  ExitRecog();
  return 0;
}

static const int MAX_CANDIDATE_NUM = 10;
zinnia::Recognizer* gRecognizer = NULL;
zinnia::Character* gCharacter = NULL;
char gResultBuffer[MAX_CANDIDATE_NUM * 3 + 1];

/*
 * @param strokes is the strokes buffer of the character.
 * (x, y) make up one point, and x and y are int16 type, their valid value are from -1 to 32767.
 * (-1, 0) is end flag of stroke, while (-1, -1) is end flag of character.
 * @param resultBuffer A buffer to receive the result string. Its size should be MAX_CANDIDATE_NUM+1.
 * @return The recognition result number. Returns -1 if error occurs.
 */
const char* CharacterRecognize(const int* strokes)
{
  gResultBuffer[0] = '\0';
  gCharacter->clear();
  int index = 0;
  for (int i = 0; strokes[i] != -1 && strokes[i+1] != -1; i += 2) {
    int x = strokes[i];
    int y = strokes[i+1];
    if (x == -1) {
      ++index;
      continue;
    }
    gCharacter->add(index, x, y);
  }
  zinnia::Result *result = gRecognizer->classify(*gCharacter, MAX_CANDIDATE_NUM);
  if (!result) {
      std::cerr << gRecognizer->what() << std::endl;
     return gResultBuffer;
  }
  for (size_t i = 0; i < result->size(); ++i) {
    strcat(gResultBuffer, result->value(i));
  }
  return gResultBuffer;
}

bool InitRecog(const char* dictFile, int width, int height)
{
  gRecognizer = zinnia::Recognizer::create();
  if (!gRecognizer->open(dictFile)) {
    std::cerr << gRecognizer->what() << std::endl;
    return false;
  }

  gCharacter = zinnia::Character::create();
  gCharacter->set_width(width);
  gCharacter->set_height(height);
	return true;
}

void ExitRecog()
{
  delete gCharacter;
  gCharacter = NULL;
  delete gRecognizer;
  gRecognizer = NULL;
}
