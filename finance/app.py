import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Select data from DB
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    stocks = db.execute("SELECT name, shares, price, symbol , (price * shares) AS total FROM holders WHERE user_id = ?", user_id)
    return render_template("index.html", cash=cash, stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure shares is > 0
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be over 0")

        # Ensure symbol is submited
        if not symbol:
            return apology("must provide symbol", 400)

        # lookup
        quote = lookup(symbol)

        # If lookup cannot find anything then aplogy
        if not quote:
            return apology("Invalid symbol", 400)

        user_id = session["user_id"]
        cost = quote["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        total_price = cost * shares

        # User dose not have enough money
        if cash < total_price:
            return apology("You do not have enough money")
        # User can buy stock
        else:
            # Update users cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)

            # Insert information into transactions
            quote_name = quote["name"]
            quote_price = quote["price"]
            type = "BUY"
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, quote_name, shares, quote_price, type, symbol)

            # Insert information into holders
            now_shares = db.execute("SELECT shares FROM holders WHERE user_id=? AND symbol=?", user_id, symbol)
            # First time to buy this symbol
            if len(now_shares) != 1:
                db.execute("INSERT INTO holders (user_id, symbol, name, shares, price) VALUES (?, ?, ?, ?, ?)",
                           user_id, symbol, quote_name, shares, quote_price)
            # If user has this symbol
            else:
                now_shares = now_shares[0]["shares"]
                db.execute("UPDATE holders SET shares = ? WHERE id = ? AND symbol=?", now_shares + shares, user_id, symbol)

            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # Select data from DB
    transactions = db.execute("SELECT name, shares, price, symbol, type, time FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # If input is null then aplogy
        if not symbol:
            return apology("Please enter a symbol")

        # lookup
        quote = lookup(symbol)

        # If lookup cannot find anything then aplogy
        if not quote:
            return apology("Invalid symbol")

        return render_template("quoted.html", quote=quote, usd=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide confirmation", 400)

        # Ensure passward = confirmation
        elif not password == confirmation:
            return apology("password does not match confirmation", 400)

        # Ensure username dose not exist
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if rows:
            return apology("This username has already existed", 400)

        # Insert username and password into DB
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure shares is > 0
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be over 0", 400)

        # Ensure symbol is submited
        if not symbol:
            return apology("must provide symbol", 400)

        # lookup
        quote = lookup(symbol)

        # If lookup cannot find anything then aplogy
        if not quote:
            return apology("Invalid symbol", 400)

        user_id = session["user_id"]
        cost = quote["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        total_price = cost * shares

        # Ensure user has shares
        now_shares = db.execute("SELECT shares FROM holders WHERE user_id=? AND symbol=?", user_id, symbol)
        if len(now_shares) != 1:
            return apology("You do not have this symbol")

        # Ensure user has enough shares
        now_shares = int(now_shares[0]["shares"])
        if now_shares < shares:
            return apology("You do not have enough shares")
        else:
            # Sell stock
            # Update users cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + total_price, user_id)
            # Insert information into transactions
            quote_name = quote["name"]
            quote_price = quote["price"]
            type = "SELL"
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, quote_name, shares, quote_price, type, symbol)

            # Update holders
            db.execute("UPDATE holders SET shares = ? WHERE id = ? AND symbol=?", now_shares - shares, user_id, symbol)

        return redirect("/")
    else:
        user_id = session["user_id"]
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

        return render_template("sell.html", symbols=symbols)


@app.route("/payment", methods=["GET", "POST"])
@login_required
def payment():
    """Payment"""
    if request.method == "POST":

        payment = int(request.form.get("payment"))

        # Ensure symbol is submited
        if not payment:
            return apology("must provide the amount", 400)

        # Ensure shares is > 0
        if not payment > 0:
            return apology("payment must be over 0")

        # Update users cash
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + payment, user_id)

        return redirect("/")
    else:
        return render_template("payment.html")
