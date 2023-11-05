from flask import Flask, render_template, request, redirect, url_for
import os
import sqlite3

app = Flask(__name__)

# Create the images folder if it doesn't exist
if not os.path.exists('images'):
    os.makedirs('images')

# Initialize the database
conn = sqlite3.connect('db/ids.db')
c = conn.cursor()

# Create the table if it doesn't exist
c.execute('''
          CREATE TABLE IF NOT EXISTS ids
          (id INTEGER PRIMARY KEY,
          status TEXT,
          photo_path TEXT)
          ''')

# Commit and close the connection
conn.commit()
conn.close()

@app.route('/')
def index():
    # Fetch data from the database
    conn = sqlite3.connect('db/ids.db')
    c = conn.cursor()
    c.execute('SELECT * FROM ids')
    ids = c.fetchall()
    conn.close()

    if not ids:
        message = "No data available. Please add data."
        return render_template('index.html', ids=ids, message=message)

    return render_template('index.html', ids=ids)

@app.route('/add_ids', methods=['GET', 'POST'])
def add_ids():
    if request.method == 'POST':
        # Get data from the form
        id = request.form['id']
        photo = request.files['photo']

        # Save the image in the images folder
        photo_path = f'static/images/{id}.{photo.filename.split(".")[-1]}'
        photo.save(photo_path)

        # Add data to the database with status as 'unknown'
        conn = sqlite3.connect('db/ids.db')
        c = conn.cursor()
        c.execute('INSERT INTO ids (id, status, photo_path) VALUES (?, ?, ?)', (id, 'unknown', photo_path))
        conn.commit()
        conn.close()

        return redirect(url_for('index'))

    return render_template('add_ids.html')

@app.route('/update_status/<int:id>/<new_status>')
def update_status(id, new_status):
    # Update status for a specific ID in the database
    conn = sqlite3.connect('db/ids.db')
    c = conn.cursor()
    c.execute('UPDATE ids SET status = ? WHERE id = ?', (new_status, id))
    conn.commit()
    conn.close()

    return "Status updated successfully"

if __name__ == '__main__':
    app.run(debug=True)
