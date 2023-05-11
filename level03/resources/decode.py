def main():
    crypt = "Q}|u`sfg~sf{}|a3"
    saved_num = 322424845
    for i in range(0, 21):
        decrypt = ""
        for j in range(0, len(crypt)):
            decrypt += chr(ord(crypt[j])^i)
        if decrypt == "Congratulations!":
            print(saved_num - i)


if __name__ == "__main__":
    main()