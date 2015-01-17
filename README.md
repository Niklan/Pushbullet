# Pushbullet
Pushbullet boilerplate for feature Drupal integration, maybe.

# Code examples
~~~php
// Initialize.
$pushbullet = new Pushbullet('YOUR ACCESS TOKEN');

// Send Note.
$pushbullet->pushNote('Title', 'Body.');

// Send Link.
$pushbullet->pushLink('Title', 'Body.', 'http://google.com/');

// Send Address.
$pushbullet->pushAddress('State of Liberty', 'Liberty Island, New York, NY, USA');

// Send List.
$pushbullet->pushList('Title', array(
  'Buy milk',
  'Buy coffee',
));

// Send File.
$pushbullet->pushFile('My cat', 'image/jpeg', 'http://example.com/cat.jpg', 'Body.');
~~~
