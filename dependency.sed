s|\\|/|g    # change all back slashes
s|\"||g     # eliminate quotes
s|/\ |\\ |g # change all spaces
s|:\\|: |g  # except the separator after colon
s|/$|\\|g   # replace last slash with backslash