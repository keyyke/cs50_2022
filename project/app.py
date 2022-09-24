import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///todo.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    """Show todo list and user can add todo and delete"""
    if request.method == "POST":
        task = request.form.get("task")
        # Insert new task into todo list
        db.execute("INSERT INTO todos (task, status) VALUES (?, ?)", task, 0)
        return redirect("/")
    else:
        # Select data from DB
        todos = db.execute("SELECT * FROM todos WHERE status = 0")
        return render_template("index.html", todos=todos)

@app.route("/all")
def all():
    """Show ALL todo list"""
    todos = db.execute("SELECT * FROM todos")
    return render_template("all.html", todos=todos)

@app.route("/finish_task", methods=["GET", "POST"])
def finish_task():
    """task is doen"""
    if request.method == "POST":
        id = request.form.get("id")
        #status = int(request.form.get("finish"))
        db.execute("UPDATE todos SET status = ? WHERE id = ?", 1, id)
        return redirect("/")
    else:
        return redirect("/")