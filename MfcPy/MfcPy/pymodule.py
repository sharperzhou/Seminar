
def load(filename):
    lines = []
    with open(filename) as file:
        for line in file:
            lines.append(line.rstrip('\n'))

    return '\r\n'.join(lines)


def save(filename, contents):
    contents = contents.replace('\r\n', '\n')
    with open(filename, 'w') as file:
        file.write(contents)

def add_one(n):
    return str(int(n)+1)
