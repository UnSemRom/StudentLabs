<template>
  <div class="wrapper-content wrapper-content--fixed">
    <section>
      <div class="container">
        <div class="auth">
          
          <div class="auth__banner">
            <catCoding />
          </div>
          <div class="auth__form">
            <h1 class="title">Войти</h1>
            <form @submit.prevent="onSubmit">
              <div class="form-item" :class="{ errorInput: $v.mail.$error }">
                <input id="email-input" type="email" placeholder="Почта" v-model="mail" :class="{ error: $v.mail.$error }" @change="$v.mail.$touch()" />
                <div class="error" v-if="!$v.mail.required">Няяя!!! Это поле обязательно</div>
                <div class="error" v-if="!$v.mail.email">Няяя!!! Это поле обязательно</div>
              </div>
              <div class="form-item" :class="{ errorInput: $v.password.$error }">
                <input id="password-input" type="password" placeholder="Пароль" v-model="password" :class="{ error: $v.password.$error }" @change="$v.password.$touch()" />
                <div class="error" v-if="!$v.password.required">Няяя!!! Это поле обязательно</div>
                <div class="error" v-if="!$v.password.minLength">Мяу...это поле должно быть не менее{{ $v.password.$params.minLength.min }} знаков</div>
              </div>
              <label class="custom-checkbox">
                <input type="checkbox" id="test1" />
                <label for="test1">Запомнить меня</label>
              </label>
              <div class="buttons-list">
                <button class="pulse" type="submit" :disabled="submitStatus === 'PENDING'">Войти</button>
              </div>
              <div class="buttons-list buttons-list--info">
                <p class v-if="submitStatus === 'OK'">Thanks for your submission!</p>
                <p class v-if="submitStatus === 'ERROR'">Please fill the form correctly.</p>
                <p class v-if="submitStatus === 'PENDING'">Sending...</p>
              </div>
              <div class="buttons-list buttons-list--info">
                <span>
                  Не зарегистриованны?
                  <router-link to="/registration">Зайдите сюда</router-link>
                </span>
              </div>
            </form>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
import { required, email, minLength } from "vuelidate/lib/validators";
import catCoding from "@/views/catCoding/index.vue";

export default {
  data() {
    return {
      mail: "",
      password: "",
      rememberMe: true,
      submitStatus: null
    };
  },

  components: {
    catCoding
  },

  validations: {
    mail: {
      required,
      email
    },
    password: {
      required,
      minLength: minLength(6)
    }
  },

  methods: {
    async onSubmit() {
      this.$v.$touch();
      if (this.$v.$invalid) {
        this.submitStatus = "ERROR";
      } else {
        const { mail, password, rememberMe } = this;
        console.log(rememberMe);
        const { data } = await this.$store.dispatch("auth/login", {
          mail,
          password,
          rememberMe
        });
        if (!data) {
          this.submitStatus = err.message;
          return;
        } else {
          this.submitStatus = "OK";
        }
        return this.$router.push({ name: "aboutCat" });
      }
    }
  }
};
</script>




<style lang="scss" scoped>
@import "@/assets/utils/colors";
.auth {
  display: flex;
}

.auth__banner,
.auth__form {
  width: 50%;
  padding: 50px;
}
.form-item .error {
  display: none;
  margin-bottom: 8px;
  font-size: 13.4px;
  color: #fc5c65;
}
.form-item.errorInput .error {
  display: block;
}
input.error {
  border-color: #fc5c65;
  animation: shake 0.3s;
}
.buttons-list {
  text-align: right;
  margin-bottom: 20px;
}
.buttons-list.buttons-list--info {
  text-align: center;
}
.buttons-list.buttons-list--info:last-child {
  margin-bottom: 0;
}
a {
  color: #444ce0;
}

label {
  text-align: left;
}

.auth__form {
  box-shadow: 0 14px 28px $second-primary-color , 0 10px 10px $second-primary-color ;
  width: 30%;
  height: 50%;
  justify-content: center;
  border-radius: 20px;
  padding: 20px;
}

.title {
  text-align: center;
}

span {
  color: $primary-color;
}

.container {
  margin-top: 10%;
}

input {
  margin-bottom: 30px;
}
</style>