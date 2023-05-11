def main():
    pass_str = "0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d"

    pass_list = pass_str.split(" ")

    pass_list = [bytearray.fromhex(x.strip("0x")).decode()[::-1] for x in pass_list]
    pass_str = "".join(pass_list)
    print(pass_str)


if __name__ == '__main__':
    main()