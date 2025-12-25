def process_file(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as fin, \
         open(output_path, 'w', encoding='utf-8') as fout:

        for line in fin:
            line = line.strip()
            line = line.strip('#')

            line = line.upper()

            # 写入处理后的行
            fout.write(line + '\n\n')


# 调用
process_file('./doc/input.txt', './doc/output.txt')