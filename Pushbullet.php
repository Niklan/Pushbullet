<?php

/**
 * @file
 * Pushbullet class.
 */
class Pushbullet {

  private $_accessKey;

  // Store API url and API calls.
  const API_URL = 'https://api.pushbullet.com';
  const API_PUSHES = '/v2/pushes';
  const API_DEVICES = '/v2/devices';
  const API_CONTACTS = '/v2/contacts';
  const API_SUBSCRIPTIONS = '/v2/subscriptions';
  const API_USER = '/v2/users/me';
  const API_UPLOAD = '/v2/upload-request';

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
   * @param $data
   * @return mixed
   * @throws \Exception
   */
  private function _request($apiCall, $data) {
    $url = self::API_URL . $apiCall;

    $curl = curl_init();

    // Create cURL options array.
    $curlOptions = array(
      CURLOPT_URL => $url,
      CURLOPT_HEADER => FALSE,
      CURLOPT_POST => TRUE,
      CURLOPT_USERPWD => $this->_accessKey,
      CURLOPT_HTTPHEADER => array(
        'Content-Type: application/json',
      ),
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_POSTFIELDS => json_encode($data),
    );

    curl_setopt_array($curl, $curlOptions);

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
    print_r($response);
    return json_decode($response);
  }

  /**
   * Push Note.
   * @param null $title
   * @param null $body
   * @return mixed
   */
  public function pushNote($title = NULL, $body = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'note',
      'title' => $title,
      'body' => $body,
    ));
  }

  /**
   * Push link.
   * @param null $title
   * @param null $body
   * @param null $url
   * @return mixed
   * @throws \Exception
   */
  public function pushLink($title = NULL, $body = NULL, $url = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'link',
      'title' => $title,
      'body' => $body,
      'url' => $url,
    ));
  }

  /**
   * Push Address.
   * @param null $name
   * @param null $address
   * @return mixed
   * @throws \Exception
   */
  public function pushAddress($name = NULL, $address = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'address',
      'name' => $name,
      'address' => $address,
    ));
  }

  /**
   * Push Checklist.
   * @param null $title
   * @param array $items
   * @return mixed
   * @throws \Exception
   * @internal param null $body
   */
  public function pushList($title = NULL, $items = array()) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'list',
      'title' => $title,
      'items' => $items,
    ));
  }


  /**
   * Push File.
   * @param null $file_name
   * @param null $file_type
   * - You can find MIME type list here: https://en.wikipedia.org/wiki/Internet_media_type
   * @param null $file_url
   * @param null $body
   * @return mixed
   * @throws \Exception
   */
  public function pushFile($file_name = NULL, $file_type = NULL, $file_url = NULL, $body = NULL) {
    return $this->_request(self::API_PUSHES, array(
      'type' => 'file',
      'file_name' => $file_name,
      'file_type' => $file_type,
      'file_url' => $file_url,
      'body' => $body,
    ));
  }

}
