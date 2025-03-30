class SourceList:
    def __init__(self):
        self.sources = {}
        self.counter = 0

    def get_sources(self):
        return self.sources

    def _get_next_counter(self):
        self.counter += 1
        return self.counter
        
    def add_source(self, text):
        for number, value in self.sources.items():
            if value == text:
                return number

        self.counter = self._get_next_counter()
        self.sources[self.counter] = text
        return self.counter
