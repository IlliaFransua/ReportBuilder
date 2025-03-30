import os
from functools import wraps

from PracticeWordReportBuilder import WordReportBuilder
from TextCleaner import TextCleaner


class ReportBuilder:
    def __init__(self, filename, section_number=1):
        self.filename = filename
        self.section_number = section_number

        self._actions = []
        self._report = WordReportBuilder(filename)

    def _add_action(self, method_name, *args, **kwargs):
        self._actions.append((method_name, args, kwargs))

    def _add_empty_line_decorator(func):
        """
        Decorator that adds an empty line before and after the execution of the wrapped function.
        """

        @wraps(func)
        def wrapper(self, *args, **kwargs):
            self._add_empty_line()
            result = func(self, *args, **kwargs)
            self._add_empty_line()
            return result

        return wrapper

    def _add_empty_line(self):
        self._add_action("_add_empty_line")

    def _remove_extra_empty_lines(self, actions):
        optimized_actions = []
        prev_action = None

        for action in actions:
            method_name, args, kwargs = action
            if method_name == '_add_empty_line' and prev_action == '_add_empty_line':
                continue
            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def _remove_empty_lines_between_text(self, actions):
        optimized_actions = []
        prev_action = None

        for i, action in enumerate(actions):
            method_name, args, kwargs = action

            if method_name == '_add_empty_line' and prev_action == 'add_text':
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_text':
                    continue

            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def _remove_empty_lines_at_edges(self, actions):
        if actions and actions[0][0] == '_add_empty_line':
            actions.pop(0)
        if actions and actions[-1][0] == '_add_empty_line':
            actions.pop()
        return actions

    def _remove_empty_lines_between_text_and_list(self, actions):
        optimized_actions = []
        prev_action = None

        for i, action in enumerate(actions):
            method_name, args, kwargs = action

            if method_name == '_add_empty_line' and prev_action == 'add_text':
                if i + 1 < len(actions) and (
                        actions[i + 1][0] == 'add_list' or actions[i + 1][0] == 'add_numbered_list'):
                    continue

            if method_name == '_add_empty_line' and (prev_action == 'add_list' or prev_action == 'add_numbered_list'):
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_text':
                    continue

            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def _remove_empty_lines_between_lists(self, actions):
        optimized_actions = []
        prev_action = None

        for i, action in enumerate(actions):
            method_name, args, kwargs = action

            if method_name == '_add_empty_line' and (prev_action == 'add_list' or prev_action == 'add_numbered_list'):
                if i + 1 < len(actions) and (
                        actions[i + 1][0] == 'add_list' or actions[i + 1][0] == 'add_numbered_list'):
                    continue

            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def _split_description_and_items(self, text):
        text = text.strip()
        lines = text.splitlines()

        lines = [line for line in lines if line.strip()]

        description = lines[0] if lines else ""

        items = "\n".join(lines[1:]) if len(lines) > 1 else ""

        return description.strip(), items

    def _remove_empty_lines_between_text_and_image(self, actions):
        optimized_actions = []
        prev_action = None

        for i, action in enumerate(actions):
            method_name, args, kwargs = action

            if method_name == '_add_empty_line' and prev_action == 'add_text':
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_image':
                    continue

            if method_name == '_add_empty_line' and prev_action == 'add_image':
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_text':
                    continue

            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def _remove_empty_lines_between_text_and_listing(self, actions):
        optimized_actions = []
        prev_action = None

        for i, action in enumerate(actions):
            method_name, args, kwargs = action

            if method_name == '_add_empty_line' and prev_action == 'add_text':
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_listing':
                    continue

            if method_name == '_add_empty_line' and prev_action == 'add_listing':
                if i + 1 < len(actions) and actions[i + 1][0] == 'add_text':
                    continue

            optimized_actions.append(action)
            prev_action = method_name

        return optimized_actions

    def add_introduction(self, text):
        cleaned_text_text = TextCleaner.clean_text(text)

        self._add_action("add_introduction", cleaned_text_text)

    @_add_empty_line_decorator
    def add_section(self, text):
        cleaned_text_text = TextCleaner.clean_text(text)

        self._add_action("add_section", cleaned_text_text)

    @_add_empty_line_decorator
    def add_sub_section(self, text):
        cleaned_text_text = TextCleaner.clean_text(text)

        self._add_action("add_sub_section", cleaned_text_text)

    @_add_empty_line_decorator
    def add_sub_sub_section(self, text):
        cleaned_text_text = TextCleaner.clean_text(text)

        self._add_action("add_sub_sub_section", cleaned_text_text)

    @_add_empty_line_decorator
    def add_text(self, text):
        cleaned_text = TextCleaner.clean_text(text)

        self._add_action("add_text", cleaned_text)

    @_add_empty_line_decorator
    def add_list(self, *args):
        if len(args) == 1 and isinstance(args[0], str):
            text = args[0]
            description, items = self._split_description_and_items(text)
        elif len(args) == 2:
            description, items = args
        else:
            raise TypeError("add_list() принимает 1 или 2 аргумента")

        cleaned_description = TextCleaner.clean_text(description)
        cleaned_items = TextCleaner.clean_items(items)
        self._add_action("add_list", cleaned_description, cleaned_items)

    @_add_empty_line_decorator
    def add_numbered_list(self, *args):
        if len(args) == 1 and isinstance(args[0], str):
            text = args[0]
            description, items = self._split_description_and_items(text)
        elif len(args) == 2:
            description, items = args
        else:
            raise TypeError("add_numbered_list() принимает 1 или 2 аргумента")

        cleaned_description = TextCleaner.clean_text(description)
        self._add_action("add_numbered_list", cleaned_description, items)

    @_add_empty_line_decorator
    def add_image(self, image_path, description):
        cleaned_description = TextCleaner.clean_text(description)

        self._add_action("add_image", image_path, cleaned_description)

    @_add_empty_line_decorator
    def add_images_of_all_files(self, directory):
        if not os.path.isdir(directory):
            raise ValueError(f"{directory} is not a directory")

        image_extensions = {'.png', '.jpg', '.jpeg', '.bmp', '.gif', '.tiff', '.svg'}

        for root, dirs, files in os.walk(directory):
            for file_name in files:
                file_path = os.path.join(root, file_name)

                if os.path.isfile(file_path) and any(file_name.lower().endswith(ext) for ext in image_extensions):
                    description = f"TEXT"
                    self.add_image(file_path, description)

    @_add_empty_line_decorator
    def add_listing(self, file_path):
        self._add_action("add_listing", file_path)

    @_add_empty_line_decorator
    def add_listings_of_all_files(self, directory):
        if not os.path.isdir(directory):
            raise ValueError(f"{directory} is not a directory")

        code_extensions = {
            '.c', '.cpp', '.h', '.py', '.java', '.js', '.ts', '.rb', '.go', '.php',
            '.html', '.css', '.sh', '.pl', '.swift', '.kt', '.scala', '.r', '.lua',
            '.m', '.sql', '.bash', '.txt', '.md'
        }

        for root, dirs, files in os.walk(directory):
            for file_name in files:
                file_path = os.path.join(root, file_name)

                if os.path.isfile(file_path) and any(file_name.lower().endswith(ext) for ext in code_extensions):
                    self.add_listing(file_path)

    @_add_empty_line_decorator
    def add_table(self, description, items):
        cleaned_description = TextCleaner.clean_text(description)

        self._add_action("add_table", cleaned_description, items)

    def add_source_list(self):
        self._add_action("add_source_list")

    def save(self):
        """
        Executes all accumulated actions and saves the document.
        """
        if not self._actions:
            return

        actions = self._remove_extra_empty_lines(self._actions)
        actions = self._remove_empty_lines_between_text(actions)
        actions = self._remove_empty_lines_at_edges(actions)
        actions = self._remove_empty_lines_between_text_and_image(actions)
        actions = self._remove_empty_lines_between_text_and_listing(actions)
        actions = self._remove_empty_lines_between_text_and_list(actions)
        actions = self._remove_empty_lines_between_lists(actions)

        for method_name, args, kwargs in actions:
            method = getattr(self._report, method_name)

            if method.__name__ == "add_table":
                current_table_number = self._report.get_current_table_number()
                self._report.add_text(f"TEXT зображено у таблиці {current_table_number}.")
                self._report._add_empty_line()
                kwargs["current_table_number"] = current_table_number

            method(*args, **kwargs)

        self._report.save()

    def _remove_section_number(self):
        self._add_action("_remove_section_number")

    def _remove_sub_section_number(self):
        self._add_action("_remove_sub_section_number")

    def _remove_sub_sub_section_number(self):
        self._add_action("_remove_sub_sub_section_number")
