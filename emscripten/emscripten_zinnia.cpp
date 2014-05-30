#include <iostream>
#include <string.h>
#include <emscripten.h>
#include "../zinnia/zinnia.h"

extern "C" {

bool InitRecog(const char* dictFile, int width, int height);
void ExitRecog();
const char* CharacterRecognize(const short* strokes);

int main(int argc, char **argv) {
  if (!InitRecog("zh_Hans.model", 140, 140)) {
    return -1;
  }

  // handwriting input of "前" character.
  short input[] = {
    42, 16, 43, 17, 44, 18, 45, 18, 46, 19, 48, 21, 51, 22, 53, 23, 55, 24, 57,
      26, 58, 26, 59, 26, 59, 27, -1, 0, 92, 14, 91, 14, 90, 14, 90, 14, 89, 15,
      87, 16, 86, 17, 84, 18, 82, 20, 79, 20, 76, 22, 75, 22, 74, 22, 74, 22, -
      1, 0, 29, 29, 30, 29, 31, 29, 33, 30, 34, 30, 36, 30, 39, 30, 43, 30, 51,
      30, 56, 30, 61, 30, 65, 30, 68, 30, 71, 30, 72, 30, 73, 30, 73, 30, 74,
      30, 75, 30, 75, 30, 76, 30, 76, 30, 77, 30, 78, 30, 80, 31, 81, 31, 82,
      31, 83, 30, 84, 30, 86, 30, 86, 29, 87, 30, 88, 30, 90, 30, 90, 30, 91,
      30, 91, 30, 92, 30, 92, 30, 93, 30, -1, 0, 39, 45, 38, 46, 38, 47, 37, 49,
      37, 52, 36, 56, 36, 62, 34, 69, 33, 76, 33, 82, 32, 87, 32, 92, 31, 98,
      30, 102, 29, 106, 29, 111, 29, 114, 28, 117, 27, 120, 27, 121, 27, 122,
      27, 122, -1, 0, 37, 47, 38, 47, 40, 47, 43, 46, 46, 46, 49, 46, 53, 46,
      55, 46, 56, 46, 56, 46, 57, 46, 58, 46, 60, 46, 61, 46, 62, 46, 63, 46,
      65, 46, 65, 46, 66, 46, 66, 46, 66, 46, 65, 46, 65, 47, 65, 47, 65, 48,
      65, 49, 65, 50, 65, 52, 65, 54, 65, 56, 64, 57, 64, 59, 64, 60, 64, 61,
      64, 62, 64, 63, 63, 64, 63, 65, 63, 67, 63, 68, 63, 68, 63, 69, 63, 70,
      63, 71, 62, 72, 62, 72, 62, 73, 62, 74, 62, 74, 62, 75, 62, 76, 62, 77,
      62, 78, 61, 79, 61, 80, 61, 81, 61, 82, 61, 83, 61, 84, 61, 84, 61, 85,
      61, 86, 61, 86, 61, 87, 61, 88, 61, 89, 61, 90, 61, 91, 61, 92, 61, 93,
      60, 94, 60, 95, 60, 95, 60, 96, 60, 96, 60, 97, 60, 97, 60, 98, 60, 100,
      60, 100, 60, 101, 60, 102, 60, 104, 59, 104, 59, 105, 59, 106, 59, 107,
      59, 107, 59, 108, 59, 109, 58, 110, 58, 110, 57, 111, 56, 110, 55, 108,
      55, 107, 55, 106, 55, 104, 55, 104, 54, 103, 54, 103, 53, 102, 52, 102,
      52, 101, -1, 0, 41, 67, 42, 67, 43, 67, 44, 67, 45, 66, 46, 66, 48, 66,
      48, 66, 49, 66, 49, 66, 50, 66, 50, 65, 51, 66, -1, 0, 39, 77, 40, 77, 41,
      77, 43, 77, 44, 77, 46, 77, 47, 77, 48, 77, 49, 77, 51, 77, 53, 77, 54,
      77, 55, 78, 56, 78, 56, 78, 57, 78, -1, 0, 69, 64, 69, 65, 69, 66, 69, 67,
      69, 69, 69, 71, 69, 72, 69, 73, 69, 74, 69, 75, 69, 76, 69, 76, 69, 77,
      69, 77, 69, 78, 69, 79, 69, 80, 69, 80, 69, 81, 69, 81, -1, 0, 85, 47, 85,
      48, 85, 49, 85, 51, 85, 53, 85, 57, 85, 60, 84, 62, 84, 65, 84, 68, 84,
      71, 84, 73, 84, 75, 84, 78, 84, 82, 84, 85, 84, 89, 84, 92, 84, 95, 84,
      97, 85, 100, 85, 102, 85, 103, 85, 104, 85, 105, 85, 106, 85, 107, 85,
      108, 85, 109, 85, 110, 85, 110, 85, 111, 84, 112, 84, 113, 84, 113, 84,
      114, 83, 114, 83, 115, 83, 115, 82, 116, 82, 117, 82, 118, 81, 118, 81,
      119, 81, 120, 80, 121, 80, 121, 80, 122, 80, 123, 80, 123, 80, 124, 79,
      124, 79, 125, 78, 125, 77, 124, 76, 123, 76, 122, 75, 121, 75, 120, 75,
      120, 75, 119, 74, 119, 74, 118, 73, 118, 73, 117, 72, 117, 72, 116, 71,
      116, 71, 115, 70, 115, -1, 0, -1, -1
  };
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
const char* CharacterRecognize(const short* strokes)
{
  gResultBuffer[0] = '\0';
  gCharacter->clear();
  int index = 0;
  for (int i = 0; strokes[i] != -1 || strokes[i+1] != -1; i += 2) {
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

} // extern "C"
