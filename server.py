from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['GET','POST'])
def receive_data():
    try:
        data = request.get_json()
        temperature = data['temperature']
        humidity = data['humidity']
        
        # Log the received data
        print(f"Received Temperature: {temperature}°C")
        print(f"Received Humidity: {humidity}%")
        
        response = {
            'status': 'success',
            'message': 'Data received',
            'data': {
                'temperature': temperature,
                'humidity': humidity
            }
        }
        return jsonify(response), 200
    except Exception as e:
        print(f"Error: {e}")
        response = {
            'status': 'fail',
            'message': 'Invalid data received'
        }
        return jsonify(response), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
