def coleman_liau_index(text):
    # Variables for counting
    sum_of_letters = 0
    sum_of_sentences = 0

    # Iterate through each word in the text
    for element in text:
        # Check if the element is alpha numeric
        if element.isalnum():
            sum_of_letters += 1
        # Check if the element is a punctuation mark
        elif element in ".!?":
            sum_of_sentences += 1

    # Converts the string into a list of words
    word_list = text.split()
    sum_of_words = len(word_list)

    # Error handling
    if sum_of_words == 0:
        return "ERROR: No words found in the text."

    average_letters = sum_of_letters / sum_of_words * 100
    average_sentences = sum_of_sentences / sum_of_words * 100

    # Compute Coleman-Liau index
    return round(0.0588 * average_letters - 0.296 * average_sentences - 15.8)


text = input("Text: ")

grade = coleman_liau_index(text)

if grade == "ERROR: No words found in the text.":
    print(grade)

if grade < 1:
    print("Before Grade 1")

elif grade > 16:
    print("Grade 16+")

else:
    print(f"Grade {grade}")
