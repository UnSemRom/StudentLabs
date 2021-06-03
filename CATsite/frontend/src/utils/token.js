export const setToken = (type = 'local', token, $http) => {
  if (type === 'session') {
    sessionStorage.setItem('token', token);
  }

  if (type === 'local') {
    localStorage.setItem('token', token);
  }

  $http.defaults.headers.common['Authorization'] = `Bearer ${token}`;

  return token;
};

export const deleteToken = ($http) => {
  sessionStorage.removeItem('token');
  localStorage.removeItem('token');

  return delete $http.defaults.headers.common['Authorization'];
};

export const getToken = ($http) => {
  const token = sessionStorage.getItem('token') || localStorage.getItem('token');

  if (token) {
    $http.defaults.headers.common['Authorization'] = `Bearer ${token}`;
  }

  return token;
};