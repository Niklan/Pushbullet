<?php

/**
 * @file
 * Pushbullet class. Can be used as standalone php class for Pushbullet.
 */
class Pushbullet {

  private $_accessKey;

  // Store API url and API calls.
  const API_PUSHES = 'https://api.pushbullet.com/v2/pushes';
  const API_DEVICES = 'https://api.pushbullet.com/v2/devices';
  const API_CONTACTS = 'https://api.pushbullet.com/v2/contacts';
  const API_SUBSCRIPTIONS = 'https://api.pushbullet.com/v2/subscriptions';
  const API_CHANNEL_INFO = 'https://api.pushbullet.com/v2/channel-info';
  const API_USER = 'https://api.pushbullet.com/v2/users/me';
  const API_UPLOAD = 'https://api.pushbullet.com/v2/upload-request';

  /**
   * Initialization.
   * @param $accessKey
   * @throws \Exception
   */
  public function __construct($accessKey) {
    if (!function_exists('curl_init')) {
      throw new Exception('cURL library is not loaded.');
    }

    $this->_accessKey = $accessKey;
  }

  /**
   * Send cURL request to API server.
   * @param $apiCall
   * @param array $data
   * @param string $method
   * @param bool $sendJson
   * @param bool $auth
   * @return mixed
   * @throws \Exception
   */
  private function _request($apiCall, $data = array(), $method = 'POST', $sendJson = TRUE, $auth = TRUE) {
    $url = $apiCall;

    if ($method == 'GET' && $data !== null) {
      $url .= '?' . http_build_query($data);
    }

    $curl = curl_init();

    // Create cURL options array.
    $curlOptions = array(
      CURLOPT_URL => $url,
      CURLOPT_HEADER => FALSE,
      CURLOPT_RETURNTRANSFER => TRUE,
    );

    curl_setopt_array($curl, $curlOptions);

    // If we need authorization.
    if ($auth) {
      curl_setopt($curl, CURLOPT_USERPWD, $this->_accessKey);
    }

    // Recipient for push. Can be email, channel tag or device iden.
    if (!empty($data['recipient'])) {
      if (filter_var($data['recipient'], FILTER_VALIDATE_EMAIL) !== false) {
        $data['email'] = $data['recipient'];
      } else {
        if (substr($data['recipient'], 0, 1) == "#") {
          $data['channel_tag'] = substr($data['recipient'], 1);
        } else {
          $data['device_iden'] = $data['recipient'];
        }
      }

      // Clear this variable. We don't need to send this.
      unset($data['recipient']);
    }

    if ($method == 'POST') {
      if ($sendJson) {
        curl_setopt($curl, CURLOPT_HTTPHEADER, array(
          'Content-Type: application/json',
        ));
        curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($data));
      }
      else {
        curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
      }
    }

    // Set method type.
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, $method);

    $response = curl_exec($curl);

    // Check for cURL errors.
    if ($response === FALSE) {
      $curlError = curl_error($curl);
      curl_close($curl);
      throw new Exception('cURL Error: ' . $curlError);
    }

    // Check for HTTP errors.
    $httpCode = curl_getinfo($curl, CURLINFO_HTTP_CODE);
    if ($httpCode >= 400) {
      curl_close($curl);
      throw new Exception('HTTP Error: ' . $httpCode);
    }

    // All fine.
    curl_close($curl);
    return json_decode($response);
  }

  /**
   * Push Note.
   * @param null $title
   * @param null $body
   * @param null $recipient
   * @return mixed
   * @throws \Exception
   */
  public function pushNote($title = NULL, $body = NULL, $recipient = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'note',
      'title' => $title,
      'body' => $body,
      'recipient' => $recipient,
    ));
  }

  /**
   * Push link.
   * @param null $title
   * @param null $body
   * @param null $url
   * @param null $recipient
   * @return mixed
   * @throws \Exception
   */
  public function pushLink($title = NULL, $body = NULL, $url = NULL, $recipient = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'link',
      'title' => $title,
      'body' => $body,
      'url' => $url,
      'recipient' => $recipient,
    ));
  }

  /**
   * Push Address.
   * @param null $name
   * @param null $address
   * @param null $recipient
   * @return mixed
   * @throws \Exception
   */
  public function pushAddress($name = NULL, $address = NULL, $recipient = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'address',
      'name' => $name,
      'address' => $address,
      'recipient' => $recipient,
    ));
  }

  /**
   * Push Checklist.
   * @param null $title
   * @param array $items
   * @param null $recipient
   * @return mixed
   * @throws \Exception
   */
  public function pushList($title = NULL, $items = array(), $recipient = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'list',
      'title' => $title,
      'items' => $items,
      'recipient' => $recipient,
    ));
  }


  /**
   * Push File.
   * @param null $file_name
   * @param null $file_type
   * - You can find MIME type list here: https://en.wikipedia.org/wiki/Internet_media_type
   * @param null $file_url
   * @param null $body
   * @param null $recipient
   * @return mixed
   * @throws \Exception
   */
  public function pushFile($file_name = NULL, $file_type = NULL, $file_url = NULL, $body = NULL, $recipient = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'file',
      'file_name' => $file_name,
      'file_type' => $file_type,
      'file_url' => $file_url,
      'body' => $body,
      'recipient' => $recipient,
    ));
  }

  /**
   * Get all pushes.
   * @param int $modifiedAfter Request pushes modified after this timestamp.
   * @return mixed
   * @throws Exception
   */
  public function getPushes($modifiedAfter = 0) {
    return $this->_request(self::API_PUSHES, array(
      'modified_after' => $modifiedAfter
    ), 'GET');
  }

  /**
   * Mark the push as dismissed. All devices displaying this push should hide
   * it from view.
   *
   * @param $iden
   * @return mixed
   * @throws \Exception
   */
  public function dismissPush($iden) {
    return $this->_request(self::API_PUSHES . '/' . $iden, array(
      'dismissed' => TRUE,
    ));
  }

  /**
   * Change list values.
   *
   * @param $iden
   * @param array $items  Update the items of a list push. The format should be
   *                      the same as the items property of the push object,
   *                      e.g. [{"checked": true, "text": "Item One"},
   *                      {"checked": true, "text": "Item Two"}].
   * @return mixed
   * @throws \Exception
   */
  public function editPushItems($iden, $items) {
    return $this->_request(self::API_PUSHES . '/' . $iden, $items);
  }

  /**
   * Delete push.
   *
   * @param $iden
   * @return mixed
   * @throws \Exception
   */
  public function deletePush($iden) {
    return $this->_request(self::API_PUSHES . '/' . $iden, array(), 'DELETE');
  }

  /**
   * Get device list.
   *
   * @return mixed
   * @throws \Exception
   */
  public function getDevices() {
    return $this->_request(self::API_DEVICES, array(), 'GET');
  }

  /**
   * Create new device.
   *
   * @param $name
   * @param string $type
   * @return mixed
   * @throws \Exception
   */
  public function createDevice($name, $type = 'stream') {
    return $this->_request(self::API_DEVICES, array(
      'nickname' => $name,
      'type' => $type,
    ), 'POST', FALSE);
  }

  /**
   * Delete device.
   *
   * @param $iden
   * @return mixed
   * @throws \Exception
   */
  public function deleteDevice($iden) {
    return $this->_request(self::API_DEVICES . '/' . $iden , array(), 'DELETE');
  }

  /**
   * Get contacts.
   *
   * @return mixed
   * @throws \Exception
   */
  public function getContacts() {
    return $this->_request(self::API_CONTACTS, array(), 'GET');
  }

  /**
   * Create contact.
   *
   * @param $name
   * @param $email
   * @return mixed
   * @throws \Exception
   */
  public function createContact($name, $email) {
    return $this->_request(self::API_CONTACTS, array(
      'name' => $name,
      'email' => $email
    ), 'POST', FALSE);
  }


  /**
   * Update contact.
   *
   * @param $iden
   * @param $name
   * @return mixed
   * @throws \Exception
   */
  public function updateContact($iden, $name) {
    return $this->_request(self::API_CONTACTS . '/' . $iden, array(
      'name' => $name,
    ), 'POST', FALSE);
  }

  /**
   * Delete contact.
   *
   * @param $iden
   * @return mixed
   * @throws \Exception
   */
  public function deleteContact($iden) {
    return $this->_request(self::API_CONTACTS . '/' . $iden , array(), 'DELETE');
  }

  /**
   * Get subscriptions.
   *
   * @return mixed
   * @throws \Exception
   */
  public function getSubscriptions() {
    return $this->_request(self::API_SUBSCRIPTIONS, array(), 'GET');
  }

  /**
   * Subscribe to channel tag.
   *
   * @param $channelTag
   * @return mixed
   * @throws \Exception
   */
  public function subscribeToChannel($channelTag) {
    return $this->_request(self::API_SUBSCRIPTIONS, array(
      'channel_tag' => $channelTag,
    ));
  }

  /**
   * Unsubscribe from channel.
   *
   * @param $iden
   * @return mixed
   * @throws \Exception
   */
  public function unsubscribeFromChannel($iden) {
    return $this->_request(self::API_SUBSCRIPTIONS. '/' . $iden , array(), 'DELETE');
  }

  /**
   * Get channel information.
   *
   * @param $tag
   * @return mixed
   * @throws \Exception
   */
  public function getChannelInfo($tag) {
    return $this->_request(self::API_CHANNEL_INFO, array(
      'tag' => $tag,
    ), 'GET');
  }

  /**
   * Get user information.
   *
   * @return mixed
   * @throws \Exception
   */
  public function getUserInfo() {
    return $this->_request(self::API_USER, array(), 'GET');
  }

  /**
   * Update user preferences.
   * WARNING! Use it with caution.
   *
   * @param array $preferences The user's preferences (overwrites existing
   *                           object).
   * @return mixed
   * @throws \Exception
   */
  public function updateUserPreferences($preferences) {
    return $this->_request(self::API_USER, array(
      'preferences' => $preferences,
    ));
  }

  /**
   * Upload file.
   *
   * @param string $filePath
   * @param null $mimeType
   * @return mixed
   * @throws \Exception
   */
  public function uploadFile($filePath, $mimeType = NULL) {
    $fullFilePath = realpath($filePath);

    if (!is_readable($fullFilePath)) {
      throw new Exception('File: Problems with file. Check your path to file and access.');
    }

    $data['file_name'] = basename($fullFilePath);

    if ($mimeType === null) {
      $data['file_type'] = mime_content_type($fullFilePath);
    } else {
      $data['file_type'] = $mimeType;
    }

    $requestAccess = $this->_request(self::API_UPLOAD, $data);
    $requestAccess->data->file = '@' . $fullFilePath;

    $this->_request($requestAccess->upload_url, $requestAccess->data, 'POST', FALSE, FALSE);

    return $requestAccess->file_url;
  }
}
