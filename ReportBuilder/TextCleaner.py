class TextCleaner:
    prev_and = "та"

    @staticmethod
    def clean_text(text):
        try:
            lines = text.split('\n')

            cleaned_lines = [TextCleaner.alternate_and(line) for line in lines]

            text = '\n'.join(cleaned_lines)
        except Exception:
            text = text
        return text.strip().strip(" -–.")

    @staticmethod
    def clean_items(items):
        return items

    @staticmethod
    def alternate_and(text):
        result = []
        words = text.split()

        for word in words:
            if word == "і" and TextCleaner.prev_and == "і":
                result.append("та")
                TextCleaner.prev_and = "та"
            elif word == "та" and TextCleaner.prev_and == "та":
                result.append("і")
                TextCleaner.prev_and = "і"
            else:
                result.append(word)

                if word == "і":
                    TextCleaner.prev_and = "і"
                elif word == "та":
                    TextCleaner.prev_and = "та"

        return " ".join(result)
