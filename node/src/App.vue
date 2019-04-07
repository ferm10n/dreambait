<template>
  <v-app dark>
    <v-content id="test">
      <v-container
        fluid
        fill-height
      >
        <v-layout
          align-center
          justify-center
        >
          <v-flex
            xs12
            sm8
            md4
          >
            <v-card
              class="elevation-12"
              light
            >
              <v-toolbar
                color="primary"
                dark
              >
                <v-toolbar-title>
                  WiFi Settings
                </v-toolbar-title>
              </v-toolbar>
              <v-card-text>
                <v-form>
                  <v-text-field name="ssid" label="WiFi Network" type="text" />
                  <v-text-field name="password" label="Password" type="text" />
                </v-form>
              </v-card-text>
            </v-card>
          </v-flex>
        </v-layout>
      </v-container>
    </v-content>
  </v-app>
</template>

<script>
export default {
  el: '#app',
  name: 'RootApp'
};
</script>

<style lang="stylus" scoped>
#test
  background-image url(./background.svg)
  background-size contain
  background-position center
</style>
