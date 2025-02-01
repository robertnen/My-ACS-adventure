import jwt
from datetime import datetime, timedelta, timezone

# Secret key from the application
SECRET_KEY = "X9zs2Fv41ZwsBUnBo0hzwPyJdgvPuQNq"

# Create an admin token
def generate_admin_token (username):
    payload = {
        "username": username,
        "isAdmin": True,
        "exp": datetime.now(tz=timezone.utc) + timedelta (minutes=15),
    }
    token = jwt.encode(payload, SECRET_KEY, algorithm="HS256")
    return token

if __name__ == "__main__":
    username = "lucy"
    admin_token = generate_admin_token(username)
    print("Generated Admin Token: ", admin_token)